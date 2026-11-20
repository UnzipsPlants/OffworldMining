// DEV-03 Startertestomgeving: tijdelijke placeholder voor een startrobot.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OSRMSRobotPlaceholder.generated.h"

class UStaticMeshComponent;

/**
 * Tijdelijke, zichtbare placeholder voor een startrobot (Digger of Builder) in de startopstelling.
 * Bevat bewust geen besturing, AI, taken of andere spelmechaniek (die horen bij latere DEV-pakketten).
 */
UCLASS()
class OFFWORLDMINING_API AOSRMSRobotPlaceholder : public AActor
{
	GENERATED_BODY()

public:
	AOSRMSRobotPlaceholder();

	/** Rol van deze placeholder ("Digger" of "Builder"), voor controle in Outliner/Details en Output Log. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OSRMS|DEV-03")
	FName RobotRole;

	/** Kubusmesh (/Engine/BasicShapes/Cube, 1 x 1 x 1 m bij schaal 1). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OSRMS|DEV-03")
	TObjectPtr<UStaticMeshComponent> Body;
};
