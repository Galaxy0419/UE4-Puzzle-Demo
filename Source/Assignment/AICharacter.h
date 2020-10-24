#pragma once

#include "AIController.h"
#include "NiagaraComponent.h"
#include "GameFramework/Character.h"

#include "AICharacter.generated.h"

UCLASS()
class ASSIGNMENT_API AAICharacter final : public ACharacter
{
	GENERATED_BODY()

private:
	UNiagaraComponent *StunNiagComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIController> AIControllerClassOverride;

	UPROPERTY()
	AAIController* ControllerInstance;

	FTimerHandle StunTimerHandle;
	void OnStunFinished();

public:
	AAICharacter();
	void BeginPlay() override;

	UFUNCTION()
	void OnCapsuleHit(UPrimitiveComponent *HitComponent,
		AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	void Stun();
};
