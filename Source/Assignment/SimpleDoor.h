#pragma once

#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"

#include "SimpleDoor.generated.h"

UCLASS()
class ASSIGNMENT_API ASimpleDoor : public AActor
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent *SimpleDoorMeshComp;
	UMaterialInstanceDynamic *DoorDynamicMaterial;
	UAudioComponent *UnlockAudioComp;

	float StopY;
	FVector CurrentLocation;

public:
	ASimpleDoor();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void Open();
};
