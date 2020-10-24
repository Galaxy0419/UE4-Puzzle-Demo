#pragma once

#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"


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
	USphereComponent *StunSphereComp;

	UMaterial *ExplosionDecal;

	UFUNCTION()
	void OnGrenadeStop(const FHitResult& ImpactResult);

	UFUNCTION()
	void OnExplosionSoundFinished();

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AStunGrenade();
	void BeginPlay() override;

	FVector ForwardVector;
};
