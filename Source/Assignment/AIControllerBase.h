#pragma once

#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "AIControllerBase.generated.h"

UCLASS()
class ASSIGNMENT_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
private:
	UAISenseConfig_Sight *AISightConfig;

	UFUNCTION()
	void OnPlayerInSight(AActor *Player, FAIStimulus Stimulus);

protected:
	UNavigationSystemV1 *NavigationSystem;
	APawn *TargetPlayer;

public:
	AAIControllerBase();
	void BeginPlay() override;
};
