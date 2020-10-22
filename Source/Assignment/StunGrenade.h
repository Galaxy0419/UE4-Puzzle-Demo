#pragma once

#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

#include "StunGrenade.generated.h"

UCLASS()
class ASSIGNMENT_API AStunGrenade : public AActor
{
	GENERATED_BODY()

private:
	UStaticMeshComponent *GrenadeMeshComp;
	UNiagaraComponent *LightningNiagComp;
	UAudioComponent *ExplosionAudioComp;
	UProjectileMovementComponent *GrenadeProjMoveComp;

	UMaterial *ExplosionDecal;
	
	UFUNCTION()
	void OnGrenadeStop(const FHitResult& ImpactResult);
	
public:
	AStunGrenade();
	void BeginPlay() override;

	FVector ForwardVector;
};
