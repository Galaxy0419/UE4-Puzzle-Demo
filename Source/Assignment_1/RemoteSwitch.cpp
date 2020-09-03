#include "RemoteSwitch.h"

#include "UObject/ConstructorHelpers.h"

#include "ItemUserWidget.h"

ARemoteSwitch::ARemoteSwitch()
	: bOpened(false)
{
	PrimaryActorTick.bCanEverTick = false;

	/* Scene Root Component */
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	RootComponent->Mobility = EComponentMobility::Static;

	/* Switch Mesh Component */
	SwitchMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch Root Mesh Component"));
	SwitchMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SwitchMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	SwitchMeshComp->SetStaticMesh(SwitchMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchOnMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_On.M_Switch_On'"));
	OnMaterial = SwitchOnMaterialAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> SwitchOffMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_Off.M_Switch_Off'"));
	OffMaterial = SwitchOffMaterialAsset.Object;

	SwitchMeshComp->Mobility = EComponentMobility::Static;
	SwitchMeshComp->SetRelativeScale3D(FVector(0.125f, 0.5f, 0.5f));
	SwitchMeshComp->SetGenerateOverlapEvents(false);
	SwitchMeshComp->SetMaterial(0, SwitchOffMaterialAsset.Object);

	/* Wiget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Remote Switch Widget"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->Mobility = EComponentMobility::Static;
	ItemWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ItemWidgetComp->SetGenerateOverlapEvents(false);
	ItemWidgetComp->SetVisibility(false);
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void ARemoteSwitch::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("Remote Switch"));
	ItemWidget->DescriptionText->SetText(FText::FromString("\nA Switch to Unlock a Specific Door in the Level.\n\nPress \"E\" to Interact"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void ARemoteSwitch::Interact()
{
	if (!bOpened) {
		bOpened = true;
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "A Remote Door is Opened");
		SwitchMeshComp->SetMaterial(0, OnMaterial);
		OnSwitchToggle.Broadcast();
	}
}
