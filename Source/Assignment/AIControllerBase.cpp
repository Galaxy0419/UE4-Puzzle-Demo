#include "AIControllerBase.h"

#include "Kismet/KismetMathLibrary.h"

AAIControllerBase::AAIControllerBase()
	: TargetPlayer(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	/* Perception */
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight Configuration"));

	AISightConfig->SightRadius = 512.0f;
	AISightConfig->LoseSightRadius = 512.0f;
	AISightConfig->PeripheralVisionAngleDegrees = 90.0f;
	AISightConfig->SetMaxAge(0);

	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(AISightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIControllerBase::OnPlayerInSight);
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
}

void AAIControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetPlayer)
		MoveToLocation(TargetPlayer->GetActorLocation());
}

void AAIControllerBase::OnPlayerInSight(AActor *Player, FAIStimulus Stimulus)
{
	APawn *PlayerPawn = Cast<APawn>(Player);
	
	if (PlayerPawn && PlayerPawn->IsPlayerControlled()) {
		if (Stimulus.WasSuccessfullySensed())
			TargetPlayer = PlayerPawn;
		else
			TargetPlayer = nullptr;
	}
}
