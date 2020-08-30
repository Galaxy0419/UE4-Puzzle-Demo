#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"

#include "Interactable.h"
#include "ExitDoor.h"

#include "FuseBox.generated.h"

UCLASS()
class ASSIGNMENT_1_API AFuseBox : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	bool bOpened;
	
	UPROPERTY(EditAnywhere)
	AExitDoor *ExitDoor;

	UMaterial *OnMaterial;
	UMaterial *OffMaterial;
	UStaticMeshComponent *FuseBoxMeshComp;
	UStaticMeshComponent *FuseMeshComp;
	UStaticMeshComponent *FuseBoxLightMeshComp;

public:
	AFuseBox();
	void BeginPlay() override;

	void Interact() override;
};
