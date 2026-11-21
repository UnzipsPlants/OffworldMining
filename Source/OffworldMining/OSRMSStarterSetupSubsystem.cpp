// DEV-03 Startertestomgeving: startopstelling van raket, HIVE en startrobots.

#include "OSRMSStarterSetupSubsystem.h"

#include "OSRMSRobotPlaceholder.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "UObject/Package.h"

DEFINE_LOG_CATEGORY_STATIC(LogOSRMSStart, Log, All);

bool UOSRMSStarterSetupSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

USceneComponent* UOSRMSStarterSetupSubsystem::FindMarker(const AActor* Actor, FName MarkerName)
{
	if (!Actor || MarkerName.IsNone())
	{
		return nullptr;
	}

	TInlineComponentArray<USceneComponent*> Components;
	Actor->GetComponents(Components);
	for (USceneComponent* Component : Components)
	{
		if (Component && Component->GetFName() == MarkerName)
		{
			return Component;
		}
	}
	return nullptr;
}

AOSRMSRobotPlaceholder* UOSRMSStarterSetupSubsystem::SpawnRobotPlaceholder(UWorld& World, const FTransform& ExitTransform, FName Role, const FVector& LocalOffset) const
{
	// De kubusmesh heeft zijn pivot in het midden (100 uu); onderzijde op de hoogte van de marker leggen.
	const FVector LocalPosition = LocalOffset + FVector(0.f, 0.f, 50.f * RobotPlaceholderScale.Z);
	const FVector WorldPosition = ExitTransform.TransformPosition(LocalPosition);
	const FTransform SpawnTransform(ExitTransform.GetRotation(), WorldPosition, RobotPlaceholderScale);

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AOSRMSRobotPlaceholder* Robot = World.SpawnActor<AOSRMSRobotPlaceholder>(AOSRMSRobotPlaceholder::StaticClass(), SpawnTransform, Params);
	if (Robot)
	{
		Robot->RobotRole = Role;
		UE_LOG(LogOSRMSStart, Log, TEXT("DEV-03: %s-placeholder geplaatst op %s (%s)."), *Role.ToString(), *WorldPosition.ToString(), *Robot->GetName());
	}
	else
	{
		UE_LOG(LogOSRMSStart, Error, TEXT("DEV-03: %s-placeholder kon niet worden geplaatst."), *Role.ToString());
	}
	return Robot;
}

void UOSRMSStarterSetupSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	const FString MapPackage = UWorld::RemovePIEPrefix(InWorld.GetPackage()->GetName());
	if (TargetMap.IsEmpty() || MapPackage != TargetMap)
	{
		return;
	}

	UE_LOG(LogOSRMSStart, Log, TEXT("DEV-03: startopstelling voor kaart %s."), *MapPackage);

	UClass* RocketCls = RocketClass.TryLoadClass<AActor>();
	UClass* HIVECls = HIVEClass.TryLoadClass<AActor>();
	if (!RocketCls || !HIVECls)
	{
		UE_LOG(LogOSRMSStart, Error, TEXT("DEV-03: klasse niet geladen (RocketClass=%s, HIVEClass=%s)."), *RocketClass.ToString(), *HIVEClass.ToString());
		return;
	}

	// Bestaande HIVE-placeholder in de kaart opzoeken; deze wordt niet verplaatst.
	AActor* HIVE = nullptr;
	int32 HIVECount = 0;
	for (TActorIterator<AActor> It(&InWorld, HIVECls); It; ++It)
	{
		if (!HIVE)
		{
			HIVE = *It;
		}
		++HIVECount;
	}
	if (!HIVE)
	{
		UE_LOG(LogOSRMSStart, Error, TEXT("DEV-03: geen actor van %s in de kaart gevonden; geen opstelling geplaatst."), *HIVECls->GetName());
		return;
	}
	if (HIVECount > 1)
	{
		UE_LOG(LogOSRMSStart, Warning, TEXT("DEV-03: %d HIVE-actors gevonden; %s wordt gebruikt."), HIVECount, *HIVE->GetName());
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Een raket die al in de kaart staat, wordt gebruikt en niet verplaatst.
	AActor* Rocket = nullptr;
	for (TActorIterator<AActor> It(&InWorld, RocketCls); It; ++It)
	{
		Rocket = *It;
		break;
	}

	if (Rocket)
	{
		UE_LOG(LogOSRMSStart, Log, TEXT("DEV-03: bestaande raket %s gebruikt (niet verplaatst)."), *Rocket->GetName());
	}
	else
	{
		// Stap 1: tijdelijke raket op de oorsprong om de positie van de HIVE-marker t.o.v. de raketroot te bepalen.
		AActor* Probe = InWorld.SpawnActor<AActor>(RocketCls, FTransform::Identity, Params);
		const USceneComponent* ProbeMarker = FindMarker(Probe, HIVEMarkerName);
		if (!ProbeMarker)
		{
			UE_LOG(LogOSRMSStart, Error, TEXT("DEV-03: marker %s niet gevonden in %s; geen raket geplaatst."), *HIVEMarkerName.ToString(), *RocketCls->GetName());
			if (Probe)
			{
				Probe->Destroy();
			}
			return;
		}
		const FTransform MarkerRelative = ProbeMarker->GetComponentTransform().GetRelativeTransform(Probe->GetActorTransform());
		Probe->Destroy();

		// Stap 2: raket zo plaatsen dat de HIVE-marker samenvalt met de positie en rotatie van de HIVE-actor.
		const FTransform HIVETransform(HIVE->GetActorQuat(), HIVE->GetActorLocation());
		const FTransform RocketTransform = MarkerRelative.Inverse() * HIVETransform;
		Rocket = InWorld.SpawnActor<AActor>(RocketCls, RocketTransform, Params);
		if (!Rocket)
		{
			UE_LOG(LogOSRMSStart, Error, TEXT("DEV-03: raket kon niet worden geplaatst."));
			return;
		}
		UE_LOG(LogOSRMSStart, Log, TEXT("DEV-03: raket %s geplaatst op %s."), *Rocket->GetName(), *Rocket->GetActorLocation().ToString());
	}

	// Controle: afstand tussen HIVE-marker en HIVE-actor.
	if (const USceneComponent* HIVEMarker = FindMarker(Rocket, HIVEMarkerName))
	{
		const double Distance = FVector::Dist(HIVEMarker->GetComponentLocation(), HIVE->GetActorLocation());
		UE_LOG(LogOSRMSStart, Log, TEXT("DEV-03: afstand %s tot HIVE-actor: %.1f cm."), *HIVEMarkerName.ToString(), Distance);
	}
	else
	{
		UE_LOG(LogOSRMSStart, Warning, TEXT("DEV-03: marker %s ontbreekt in %s."), *HIVEMarkerName.ToString(), *Rocket->GetName());
	}

	// Controle: aanwezigheid van de grondstofinvoer (alleen registratie, geen functionaliteit).
	if (const USceneComponent* InputMarker = FindMarker(Rocket, ResourceInputMarkerName))
	{
		UE_LOG(LogOSRMSStart, Log, TEXT("DEV-03: %s aanwezig op %s."), *ResourceInputMarkerName.ToString(), *InputMarker->GetComponentLocation().ToString());
	}
	else
	{
		UE_LOG(LogOSRMSStart, Warning, TEXT("DEV-03: marker %s ontbreekt in %s."), *ResourceInputMarkerName.ToString(), *Rocket->GetName());
	}

	// Startrobots zichtbaar bij de robotuitvoer.
	const USceneComponent* ExitMarker = FindMarker(Rocket, RobotExitMarkerName);
	if (!ExitMarker)
	{
		UE_LOG(LogOSRMSStart, Error, TEXT("DEV-03: marker %s ontbreekt in %s; geen robots geplaatst."), *RobotExitMarkerName.ToString(), *Rocket->GetName());
		return;
	}
	const FTransform ExitTransform(ExitMarker->GetComponentQuat(), ExitMarker->GetComponentLocation());
	SpawnRobotPlaceholder(InWorld, ExitTransform, TEXT("Digger"), DiggerOffset);
	SpawnRobotPlaceholder(InWorld, ExitTransform, TEXT("Builder"), BuilderOffset);
}
