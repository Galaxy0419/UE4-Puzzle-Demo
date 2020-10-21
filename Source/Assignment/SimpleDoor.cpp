#include "SimpleDoor.h"

#include "Kismet/KismetMaterialLibrary.h"

#define DOOR_SPEED	64.0f

ASimpleDoor::ASimpleDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SimpleDoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Simple Door Root Mesh Component"));
	RootComponent = SimpleDoorMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	SimpleDoorMeshComp->SetStaticMesh(DoorMeshAsset.Object);

	SimpleDoorMeshComp->SetRelativeScale3D(FVector(1.0f, 2.0f, 3.0f));

	UnlockAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Unlock Audio Component"));
	UnlockAudioComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundWave>
		DoorUnlockSoundAsset(TEXT("SoundWave'/Game/Audios/SW_DoorUnlock.SW_DoorUnlock'"));
	UnlockAudioComp->SetSound(DoorUnlockSoundAsset.Object);

	UnlockAudioComp->bAutoActivate = false;
}

void ASimpleDoor::BeginPlay()
{
	Super::BeginPlay();

	UMaterial *DoorMaterial = LoadObject<UMaterial>(nullptr, TEXT("Material'/Game/Materials/M_Door.M_Door'"));
	DoorDynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DoorMaterial);
	SimpleDoorMeshComp->SetMaterial(0, DoorDynamicMaterial);

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

void ASimpleDoor::Open()
{
	UnlockAudioComp->Play();
	SetActorTickEnabled(true);
	DoorDynamicMaterial->SetScalarParameterValue("Switch", 1.0f);
};
