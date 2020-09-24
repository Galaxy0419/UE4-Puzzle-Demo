#pragma once

#include "GameFramework/Actor.h"

#include "Interactable.h"
#include "ExitDoor.h"

#include "ExitDoorSwitch.generated.h"

UCLASS()
class ASSIGNMENT_API AExitDoorSwitch final : public AActor, public IInteractable
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent *SwitchBaseMeshComp;
	UStaticMeshComponent *SwitchMeshComp;

	bool bDoorOpened;

	UPROPERTY(EditAnywhere)
	AExitDoor *ExitDoor;
	
	FRotator SwitchCurrentRotation;

public:
	AExitDoorSwitch();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	bool bFuseFound;

	void Interact() override;
};
