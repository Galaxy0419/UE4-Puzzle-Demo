#include "BinaryLight.h"

ABinaryLight::ABinaryLight()
	: bLightOn(false)
{
	PrimaryActorTick.bCanEverTick = false;

	/* Switch Mesh Component */
	LightMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Root Mesh Component"));
	RootComponent = LightMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	LightMeshComp->SetStaticMesh(SwitchMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchOnMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_On.M_Switch_On'"));
	OnMaterial = SwitchOnMaterialAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchOffMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_Off.M_Switch_Off'"));
	OffMaterial = SwitchOffMaterialAsset.Object;

	LightMeshComp->Mobility = EComponentMobility::Static;
	LightMeshComp->SetRelativeScale3D(FVector(0.5f, 0.125f, 0.5f));
	LightMeshComp->SetGenerateOverlapEvents(false);
	LightMeshComp->SetMaterial(0, SwitchOffMaterialAsset.Object);
}
