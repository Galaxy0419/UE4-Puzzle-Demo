#include "LevelAIController.h"

void ALevelAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
	if (TargetPlayer)
		MoveToLocation(TargetPlayer->GetActorLocation());
	else
		MoveToLocation(NavigationSystem->GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), 1024.0f));
}
