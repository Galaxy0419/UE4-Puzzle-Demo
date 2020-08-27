#include "SimpleKey.h"

#include "UObject/ConstructorHelpers.h"

ASimpleKey::ASimpleKey()
{
	PrimaryActorTick.bCanEverTick = false;

	SimpleKeyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Simple Key Root Mesh Component"));
	RootComponent = SimpleKeyMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SimpleKeyMeshAsset(TEXT("StaticMesh'/Game/Meshes/SM_Simple_Key.SM_Simple_Key'"));
	SimpleKeyMeshComp->SetStaticMesh(SimpleKeyMeshAsset.Object);

	SimpleKeyMeshComp->SetRelativeScale3D(FVector(0.25f));
	SimpleKeyMeshComp->SetCollisionProfileName("Trigger");
	SimpleKeyMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ASimpleKey::OnKeyBeginOverlap);
}

void ASimpleKey::OnKeyBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	Interact();
}

void ASimpleKey::Interact()
{
	SimpleDoorToUnlock->Open();
	Destroy();
}
