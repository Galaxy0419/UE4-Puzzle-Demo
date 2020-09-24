#include "LevelAIController.h"

void ALevelAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
	if (TargetPlayer) {
		MoveToLocation(TargetPlayer->GetActorLocation());
	} else {
		FNavLocation RandLocation;
		NavigationSystem->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 1024.0f, RandLocation);
		MoveToLocation(RandLocation.Location);	
	}
}
