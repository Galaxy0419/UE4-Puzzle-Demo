#pragma once

#include "AIControllerBase.h"

#include "FuseAIController.generated.h"

UCLASS()
class ASSIGNMENT_API AFuseAIController final : public AAIControllerBase
{
	GENERATED_BODY()

private:
	uint8 PatrolIndex;
	TArray<FVector> PatrolPoints;

public:
	AFuseAIController();
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
