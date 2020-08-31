#include "ExitDoor.h"

#define DOOR_SPEED	64.0f

AExitDoor::AExitDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ExitBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Exit Root Box Compoent"));
	RootComponent = ExitBoxComp;

	ExitBoxComp->SetBoxExtent(FVector(8.0f, 400.0f, 200.0f), false);
	ExitBoxComp->ComponentTags.Add("Exit");

	ExitDoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exit Door Mesh Component"));
	ExitDoorMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	ExitDoorMeshComp->SetStaticMesh(DoorMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> DoorMaterialAsset(TEXT("Material'/Game/Materials/M_Flat_Blue.M_Flat_Blue'"));
	ExitDoorMeshComp->SetMaterial(0, DoorMaterialAsset.Object);

	ExitDoorMeshComp->SetRelativeScale3D(FVector(0.25f, 8.1f, 4.0f));
}

void AExitDoor::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentLocation = ExitDoorMeshComp->GetRelativeLocation();
	StopZ = CurrentLocation.Z + 400.0f;
}

void AExitDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((CurrentLocation.Z += DeltaTime * DOOR_SPEED) < StopZ) {
		ExitDoorMeshComp->SetRelativeLocation(CurrentLocation);
	} else {
		ExitDoorMeshComp->DestroyComponent();
		SetActorTickEnabled(false);
	}
}
