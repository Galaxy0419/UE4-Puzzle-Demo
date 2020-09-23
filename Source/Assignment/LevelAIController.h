#pragma once

#include "AIControllerBase.h"

#include "LevelAIController.generated.h"

UCLASS()
class ASSIGNMENT_API ALevelAIController : public AAIControllerBase
{
	GENERATED_BODY()
	
public:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
