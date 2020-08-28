#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"

#include "ExitDoor.h"

#include "FuseBox.generated.h"

UCLASS()
class ASSIGNMENT_1_API AFuseBox : public AActor
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

	UFUNCTION()
	void OnFuseBoxBeginOverlap(AActor *OverlappedActor, AActor *OtherActor);

public:
	AFuseBox();
};
