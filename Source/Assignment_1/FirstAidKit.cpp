#include "FirstAidKit.h"

#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"

#include "PlayerCharacter.h"

#include "ItemUserWidget.h"

#define RECOVER_HEALTH	0.25f

AFirstAidKit::AFirstAidKit()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Scene Root Component */
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	RootComponent->Mobility = EComponentMobility::Static;

	/* Switch Mesh Component */
	FirstAidKitMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("First Aid Kit Root Mesh Component"));
	FirstAidKitMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FirstAidKidMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	FirstAidKitMeshComp->SetStaticMesh(FirstAidKidMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> FirstAidKidMaterialAsset(TEXT("Material'/Game/Materials/M_Flat_Green.M_Flat_Green'"));
	FirstAidKitMeshComp->SetMaterial(0, FirstAidKidMaterialAsset.Object);

	FirstAidKitMeshComp->Mobility = EComponentMobility::Static;
	FirstAidKitMeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.25f));
	FirstAidKitMeshComp->SetGenerateOverlapEvents(true);
	FirstAidKitMeshComp->SetCollisionProfileName("Trigger");

	/* Wiget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("First Aid Kit Widget"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->Mobility = EComponentMobility::Static;
	ItemWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void AFirstAidKit::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("First Aid Kit"));
	ItemWidget->DescriptionText->SetText(FText::FromString("\nA First Aid Kit to Restore Small Amount of Health.\n\nPress \"E\" to Use"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void AFirstAidKit::Interact()
{
	if (Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Health < 1.0f) {
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->TakeDamage(RECOVER_HEALTH, FDamageEvent(), nullptr, this);
		Destroy();
	}
} 
