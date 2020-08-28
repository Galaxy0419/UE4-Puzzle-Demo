#include "RemoteSwitch.h"

#include "UObject/ConstructorHelpers.h"

ARemoteSwitch::ARemoteSwitch()
	: bOpened(false)
{
	PrimaryActorTick.bCanEverTick = false;

	SwitchMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch Root Mesh Component"));
	RootComponent = SwitchMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	SwitchMeshComp->SetStaticMesh(SwitchMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchOnMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_On.M_Switch_On'"));
	OnMaterial = SwitchOnMaterialAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchOffMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_Off.M_Switch_Off'"));
	OffMaterial = SwitchOffMaterialAsset.Object;

	SwitchMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ARemoteSwitch::OnSwitchBeginOverlap);
	SwitchMeshComp->SetRelativeScale3D(FVector(0.125f, 0.5f, 0.5f));
	SwitchMeshComp->SetMaterial(0, SwitchOffMaterialAsset.Object);
	SwitchMeshComp->SetCollisionProfileName("Trigger");
}

void ARemoteSwitch::OnSwitchBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (!bOpened) {
		bOpened = true;
		SwitchMeshComp->SetMaterial(0, OnMaterial);
		OnSwitchToggle.Broadcast();
	}
}
