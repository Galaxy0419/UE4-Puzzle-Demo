#pragma once

#include "AIController.h"
#include "GameFramework/Character.h"

#include "AICharacter.generated.h"

UCLASS()
class ASSIGNMENT_1_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIController> AIControllerClassOverride;

public:
	AAICharacter();
	void BeginPlay() override;
};
