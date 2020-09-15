#include "SimpleDoor.h"

#define DOOR_SPEED	64.0f

ASimpleDoor::ASimpleDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SimpleDoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Simple Door Root Mesh Component"));
	RootComponent = SimpleDoorMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	SimpleDoorMeshComp->SetStaticMesh(DoorMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> DoorMaterialAsset(TEXT("Material'/Game/Materials/M_Flat_Blue.M_Flat_Blue'"));
	SimpleDoorMeshComp->SetMaterial(0, DoorMaterialAsset.Object);

	SimpleDoorMeshComp->SetRelativeScale3D(FVector(1.0f, 2.0f, 3.0f));
}

void ASimpleDoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetActorLocation();
	StopY = CurrentLocation.Y - 200.0f;
}

void ASimpleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((CurrentLocation.Y -= DeltaTime * DOOR_SPEED) > StopY)
		SetActorLocation(CurrentLocation);
	else
		Destroy();
}
