#include "AIControllerBase.h"

#include "Perception/AIPerceptionComponent.h"

AAIControllerBase::AAIControllerBase()
	: TargetPlayer(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	/* Perception */
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	UAISenseConfig_Sight *AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight Configuration"));

	AISightConfig->SightRadius = 512.0f;
	AISightConfig->LoseSightRadius = 512.0f;
	AISightConfig->PeripheralVisionAngleDegrees = 90.0f;
	AISightConfig->SetMaxAge(0);

	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AAIController::GetPerceptionComponent()->SetDominantSense(AISightConfig->GetSenseImplementation());
	AAIController::GetPerceptionComponent()->ConfigureSense(*AISightConfig);
	AAIController::GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerBase::OnPlayerInSight);
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
}

void AAIControllerBase::OnPlayerInSight(AActor *Player, FAIStimulus Stimulus)
{
	APawn *PlayerPawn = Cast<APawn>(Player);
	
	if (PlayerPawn && PlayerPawn->IsPlayerControlled()) {
		if (Stimulus.WasSuccessfullySensed()) {
			TargetPlayer = PlayerPawn;
			MoveToActor(TargetPlayer);
		} else {
			TargetPlayer = nullptr;
			StopMovement();
		}
	}
}
