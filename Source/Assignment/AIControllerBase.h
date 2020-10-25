#pragma once

#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/AISenseConfig_Sight.h"

#include "AIControllerBase.generated.h"

UCLASS()
class ASSIGNMENT_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
private:
	UFUNCTION()
	void OnPlayerInSight(AActor *Player, FAIStimulus Stimulus);

protected:
	APawn *TargetPlayer;
	UNavigationSystemV1 *NavigationSystem;

public:
	AAIControllerBase();
	void BeginPlay() override;
};
