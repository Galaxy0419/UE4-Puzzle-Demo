#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "SimpleDoor.generated.h"

UCLASS()
class ASSIGNMENT_API ASimpleDoor : public AActor
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent *SimpleDoorMeshComp;
	UMaterialInstanceDynamic *DoorDynamicMaterial;

	float StopY;
	FVector CurrentLocation;

public:
	ASimpleDoor();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void Open();
};
