#include "SimpleKey.h"

#include "Kismet/GameplayStatics.h"

#include "ItemUserWidget.h"
#include "PlayerCharacter.h"

ASimpleKey::ASimpleKey()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Scene Root Component */
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	RootComponent->Mobility = EComponentMobility::Static;

	/* Key Mesh Component */
	SimpleKeyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Simple Key Mesh Component"));
	SimpleKeyMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SimpleKeyMeshAsset(TEXT("StaticMesh'/Game/Meshes/SM_Simple_Key.SM_Simple_Key'"));
	SimpleKeyMeshComp->SetStaticMesh(SimpleKeyMeshAsset.Object);

	SimpleKeyMeshComp->Mobility = EComponentMobility::Static;
	SimpleKeyMeshComp->SetGenerateOverlapEvents(false);
	SimpleKeyMeshComp->SetRelativeScale3D(FVector(0.25f));

	/* Widget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Simple Key Widget"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->Mobility = EComponentMobility::Static;
	ItemWidgetComp->SetGenerateOverlapEvents(false);
	ItemWidgetComp->SetRelativeLocation(FVector(-32.0f, 32.0f, 64.0f));
	ItemWidgetComp->SetVisibility(false);
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void ASimpleKey::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(),
		nullptr, TEXT("WidgetBlueprint'/Game/UIs/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("Simple Key"));
	ItemWidget->DescriptionText->SetText(FText::FromString("\nA Simple Key to Unlock a Specific Door in the Level.\n\nPress \"E\" to Pickup"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void ASimpleKey::Interact(APlayerCharacter *Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "A Door is Opened");
	SimpleDoorToUnlock->Open();
	Player->HUDWBP->KeyNumberText->SetText(FText::FromString(FString::FromInt(Player->KeyNumber += 1)));
	Destroy();
}
