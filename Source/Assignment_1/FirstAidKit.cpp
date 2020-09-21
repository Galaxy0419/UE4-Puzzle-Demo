#include "FirstAidKit.h"

#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceConstant.h"

#include "ItemUserWidget.h"
#include "PlayerCharacter.h"

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

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>
		FirstAidKidMaterialAsset(TEXT("MaterialInstanceConstant'/Game/Materials/MI_Flat_First_Aid_Kit_Inter.MI_Flat_First_Aid_Kit_Inter'"));
	FirstAidKitMeshComp->SetMaterial(0, FirstAidKidMaterialAsset.Object);

	FirstAidKitMeshComp->Mobility = EComponentMobility::Static;
	FirstAidKitMeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.25f));
	FirstAidKitMeshComp->SetGenerateOverlapEvents(false);

	/* Wiget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("First Aid Kit Widget"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->Mobility = EComponentMobility::Static;
	ItemWidgetComp->SetGenerateOverlapEvents(false);
	ItemWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ItemWidgetComp->SetVisibility(false);
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void AFirstAidKit::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("First Aid Kit"));
	ItemWidget->DescriptionText->SetText(FText::FromString(
		"A First Aid Kit to Restore Small Amount of Health.\n\nNote: You can only use it when you are hurt.\n\nPress \"E\" to Use"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void AFirstAidKit::Interact()
{
	if (Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Health < 1.0f) {
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->TakeDamage(RECOVER_HEALTH, FDamageEvent(), nullptr, this);

		APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		PlayerCharacter->HUDWBP->FirstAidKitNumberText->SetText(FText::FromString(FString::FromInt(PlayerCharacter->FirstAidKitNumber += 1)));

		Destroy();
	}
} 
