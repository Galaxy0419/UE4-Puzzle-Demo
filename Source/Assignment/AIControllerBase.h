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
	UNavigationSystemV1 *NavigationSystem;
	UAISenseConfig_Sight *AISightConfig;

	APawn *TargetPlayer;
	FRotator NewRotation;

	UFUNCTION()
	void OnPlayerInSight(AActor *Player, FAIStimulus Stimulus);

public:
	AAIControllerBase();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
};
