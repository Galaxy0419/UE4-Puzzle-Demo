#pragma once

#include "AIControllerBase.h"

#include "FuseAIController.generated.h"

UCLASS()
class ASSIGNMENT_API AFuseAIController : public AAIControllerBase
{
	GENERATED_BODY()
	
private:
	uint8 ProtalIndex;
	TArray<FVector> ProtalPoints;

public:
	AFuseAIController();
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
