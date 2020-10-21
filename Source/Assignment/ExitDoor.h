#pragma once

#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"

#include "ExitDoor.generated.h"

UCLASS()
class ASSIGNMENT_API AExitDoor final : public AActor
{
	GENERATED_BODY()
	
private:
	UBoxComponent *ExitBoxComp;
	UStaticMeshComponent *ExitDoorMeshComp;
	UMaterialInstanceDynamic *DoorDynamicMaterial;
	UAudioComponent *OpenAudioComp;

	float StopZ;
	FVector CurrentLocation;

public:	
	AExitDoor();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void Open();
};
