#include "BinaryLight.h"

ABinaryLight::ABinaryLight()
	: bLightOn(false)
{
	PrimaryActorTick.bCanEverTick = false;

	/* Switch Mesh Component */
	SwitchMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Root Mesh Component"));
	RootComponent = SwitchMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	SwitchMeshComp->SetStaticMesh(SwitchMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchOnMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_On.M_Switch_On'"));
	OnMaterial = SwitchOnMaterialAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchOffMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_Off.M_Switch_Off'"));
	OffMaterial = SwitchOffMaterialAsset.Object;

	SwitchMeshComp->Mobility = EComponentMobility::Static;
	SwitchMeshComp->SetRelativeScale3D(FVector(0.5f, 0.125f, 0.5f));
	SwitchMeshComp->SetGenerateOverlapEvents(false);
	SwitchMeshComp->SetMaterial(0, SwitchOffMaterialAsset.Object);
}
