#include "Fuse.h"

#include "Kismet/GameplayStatics.h"

#include "ItemUserWidget.h"
#include "PlayerCharacter.h"

AFuse::AFuse()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Fuse Mesh Component */
	FuseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fuse Root Mesh Component"));
	RootComponent = FuseMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FuseMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	FuseMeshComp->SetStaticMesh(FuseMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> FuseMaterialAsset(TEXT("Material'/Game/Materials/M_Flat_Fuse_Inter.M_Flat_Fuse_Inter'"));
	FuseMeshComp->SetMaterial(0, FuseMaterialAsset.Object);

	FuseMeshComp->Mobility = EComponentMobility::Static;
	FuseMeshComp->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.5f));
	FuseMeshComp->SetGenerateOverlapEvents(false);

	/* Widget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Fuse Widget"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->Mobility = EComponentMobility::Static;
	ItemWidgetComp->SetGenerateOverlapEvents(false);
	ItemWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ItemWidgetComp->SetVisibility(false);
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void AFuse::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(),
		nullptr, TEXT("WidgetBlueprint'/Game/UIs/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("Fuse"));
	ItemWidget->DescriptionText->SetText(FText::FromString("\nThe Fuse to Unlock the Exit Door.\n\nPress \"E\" to Pickup"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void AFuse::Interact(APlayerCharacter *Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "You Found the Fuse!");
	Player->HUDWBP->FuseNumberText->SetText(FText::FromString(FString::FromInt(Player->FuseNumber += 1)));
	Destroy();
}
