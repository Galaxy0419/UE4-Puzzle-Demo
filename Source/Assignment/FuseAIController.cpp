#include "FuseAIController.h"

AFuseAIController::AFuseAIController()
	: ProtalIndex(0), ProtalPoints({
		FVector(-1300.0f, 480.0f, -154.0f),
		FVector(-2060.0f, 615.0f, -154.0f),
		FVector(-1400.0f, 1000.0f, -154.0f)})
{
}

void AFuseAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
	if (TargetPlayer)
		MoveToLocation(TargetPlayer->GetActorLocation());
	else
		MoveToLocation(ProtalPoints[(++ProtalIndex) % ProtalPoints.Num()]);
}
