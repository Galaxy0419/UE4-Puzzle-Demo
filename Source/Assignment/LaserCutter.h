#pragma once

#include "GameFramework/Actor.h"

#include "LaserCutter.generated.h"

UCLASS()
class ASSIGNMENT_API ALaserCutter final : public AActor
{
	GENERATED_BODY()

private:
	UStaticMeshComponent *LaserMeshComp;

	UPROPERTY(EditAnywhere)
	FVector LerpStart;

	UPROPERTY(EditAnywhere)
	FVector LerpEnd;

	float TimeElapsed;
	FVector LerpCurrent;

public:
	ALaserCutter();
	void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnLaserBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
