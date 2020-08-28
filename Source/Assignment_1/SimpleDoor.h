#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "SimpleDoor.generated.h"

UCLASS()
class ASSIGNMENT_1_API ASimpleDoor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *SimpleDoorMeshComp;

	float StopY;
	FVector CurrentLocation;

public:
	ASimpleDoor();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	FORCEINLINE void Open() { SetActorTickEnabled(true); };
};
