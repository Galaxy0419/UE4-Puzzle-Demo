#pragma once

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "ExitDoor.generated.h"

UCLASS()
class ASSIGNMENT_1_API AExitDoor : public AActor
{
	GENERATED_BODY()
	
private:
	UBoxComponent *ExitBoxComp;
	UStaticMeshComponent *ExitDoorMeshComp;

	float StopZ;
	FVector CurrentLocation;

public:	
	AExitDoor();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
};
