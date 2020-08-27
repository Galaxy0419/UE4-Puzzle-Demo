#include "SimpleDoor.h"

#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"

#define DOOR_SPEED	64.0f

ASimpleDoor::ASimpleDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SimpleDoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Simple Door Root Mesh Component"));
	RootComponent = SimpleDoorMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	SimpleDoorMeshComp->SetStaticMesh(DoorMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> DoorMaterialAsset(TEXT("Material'/Engine/EditorMeshes/ColorCalibrator/M_GreyBall.M_GreyBall'"));
	SimpleDoorMeshComp->SetMaterial(0, DoorMaterialAsset.Object);

	SimpleDoorMeshComp->SetRelativeScale3D(FVector(0.25f, 1.5f, 2.1f));
}

void ASimpleDoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetActorLocation();
	StopY = CurrentLocation.Y - 150.0f;
}

void ASimpleDoor::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);

	if ((CurrentLocation.Y -= DeltaSecond * DOOR_SPEED) > StopY)
		SetActorLocation(CurrentLocation);
	else
		Destroy();
}