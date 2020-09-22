#include "ExitDoor.h"

#include "Kismet/KismetMaterialLibrary.h"

#define DOOR_SPEED	64.0f

AExitDoor::AExitDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	ExitBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Exit Root Box Compoent"));
	RootComponent = ExitBoxComp;

	ExitBoxComp->SetBoxExtent(FVector(32.0f, 800.0f, 275.0f), false);
	ExitBoxComp->ComponentTags.Add("Exit");

	ExitDoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exit Door Mesh Component"));
	ExitDoorMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	ExitDoorMeshComp->SetStaticMesh(DoorMeshAsset.Object);

	ExitDoorMeshComp->SetRelativeScale3D(FVector(1.0f, 16.0f, 5.5f));
}

void AExitDoor::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterial *DoorMaterial = LoadObject<UMaterial>(nullptr, TEXT("Material'/Game/Materials/M_Door.M_Door'"));
	DoorDynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DoorMaterial);
	ExitDoorMeshComp->SetMaterial(0, DoorDynamicMaterial);

	CurrentLocation = ExitDoorMeshComp->GetRelativeLocation();
	StopZ = CurrentLocation.Z + 500.0f;
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

void AExitDoor::Open()
{
	DoorDynamicMaterial->SetScalarParameterValue("Switch", 1.0f);
	SetActorTickEnabled(true);
}
