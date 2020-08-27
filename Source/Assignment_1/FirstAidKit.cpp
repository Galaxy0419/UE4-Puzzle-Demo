#include "FirstAidKit.h"

#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"

#include "PlayerCharacter.h"

#define RECOVER_HEALTH	0.25f

AFirstAidKit::AFirstAidKit()
{
	PrimaryActorTick.bCanEverTick = false;

	FirstAidKitMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First Aid Kit Root Mesh Component"));
	RootComponent = FirstAidKitMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FirstAidKidMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	FirstAidKitMeshComp->SetStaticMesh(FirstAidKidMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> FirstAidKidMaterialAsset(TEXT("Material'/Game/Materials/M_Flat_Green.M_Flat_Green'"));
	FirstAidKitMeshComp->SetMaterial(0, FirstAidKidMaterialAsset.Object);

	FirstAidKitMeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.25f));
	FirstAidKitMeshComp->SetGenerateOverlapEvents(true);
	FirstAidKitMeshComp->SetCollisionProfileName("Trigger");
	FirstAidKitMeshComp->Mobility = EComponentMobility::Static;
}

void AFirstAidKit::Interact()
{
	if (Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Health < 1.0f) {
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->TakeDamage(RECOVER_HEALTH, FDamageEvent(), nullptr, this);
		Destroy();
	}
} 
