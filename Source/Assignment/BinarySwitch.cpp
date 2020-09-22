#include "BinarySwitch.h"

#include "Kismet/GameplayStatics.h"

#include "ItemUserWidget.h"
#include "MainLevelScriptActor.h"

ABinarySwitch::ABinarySwitch()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Switch Mesh Component */
	SwitchMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Binary Switch Root Mesh Component"));
	RootComponent = SwitchMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	SwitchMeshComp->SetStaticMesh(SwitchMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchMaterialAsset(TEXT("Material'/Game/Materials/M_Door.M_Door'"));
	SwitchMeshComp->SetMaterial(0, SwitchMaterialAsset.Object);

	SwitchMeshComp->Mobility = EComponentMobility::Static;
	SwitchMeshComp->SetRelativeScale3D(FVector(0.125f, 0.5f, 0.5f));
	SwitchMeshComp->SetGenerateOverlapEvents(false);

	/* Wiget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Binary Switch Widget"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->Mobility = EComponentMobility::Static;
	ItemWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ItemWidgetComp->SetGenerateOverlapEvents(false);
	ItemWidgetComp->SetVisibility(false);
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void ABinarySwitch::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("Binary Switch"));
	ItemWidget->DescriptionText->SetText(FText::FromString("\nA Binary Switch to Unlock a Door in the Level.\n\nPress \"E\" to Interact"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void ABinarySwitch::Interact()
{
	Cast<AMainLevelScriptActor>(GetWorld()->GetLevelScriptActor())->UpdateBinaryLight(LightMasks);
}
