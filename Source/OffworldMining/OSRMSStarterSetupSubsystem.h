// DEV-03 Startertestomgeving: startopstelling van raket, HIVE en startrobots.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UObject/SoftObjectPath.h"
#include "OSRMSStarterSetupSubsystem.generated.h"

class AOSRMSRobotPlaceholder;
class USceneComponent;

/**
 * Zet bij het starten van de testkaart (instelling TargetMap) de startopstelling neer:
 * - BP_Rocket wordt zo geplaatst dat de marker HIVE_Position samenvalt met de bestaande HIVE-placeholder in de kaart;
 * - een Digger- en een Builder-placeholder worden zichtbaar bij de marker RobotExit_Position geplaatst.
 * De bestaande HIVE-placeholder en de bestaande HIVE-camerapawn worden niet verplaatst of gewijzigd.
 * Alle paden, markernamen, offsets en schaal staan in Config/DefaultGame.ini.
 * Geen landing, boren of uitklappen (buiten DEV-03-scope volgens besluit van de projecteigenaar).
 */
UCLASS(Config = Game)
class OFFWORLDMINING_API UOSRMSStarterSetupSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

protected:
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

private:
	/** Lange pakketnaam van de kaart waarin de opstelling wordt gezet, bijv. /Game/Maps/L_Test_HIVE. */
	UPROPERTY(Config)
	FString TargetMap;

	UPROPERTY(Config)
	FSoftClassPath RocketClass;

	UPROPERTY(Config)
	FSoftClassPath HIVEClass;

	UPROPERTY(Config)
	FName HIVEMarkerName;

	UPROPERTY(Config)
	FName RobotExitMarkerName;

	UPROPERTY(Config)
	FName ResourceInputMarkerName;

	/** Offset in lokale ruimte van RobotExit_Position (cm). [Aanname] tijdelijke testwaarde. */
	UPROPERTY(Config)
	FVector DiggerOffset = FVector::ZeroVector;

	/** Offset in lokale ruimte van RobotExit_Position (cm). [Aanname] tijdelijke testwaarde. */
	UPROPERTY(Config)
	FVector BuilderOffset = FVector::ZeroVector;

	/** Schaal van de kubus-placeholders (1 = 1 x 1 x 1 m). [Aanname] tijdelijke testmaat. */
	UPROPERTY(Config)
	FVector RobotPlaceholderScale = FVector::OneVector;

	static USceneComponent* FindMarker(const AActor* Actor, FName MarkerName);

	AOSRMSRobotPlaceholder* SpawnRobotPlaceholder(UWorld& World, const FTransform& ExitTransform, FName Role, const FVector& LocalOffset) const;
};
