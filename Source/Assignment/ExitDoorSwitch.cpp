#include "ExitDoorSwitch.h"

#include "ItemUserWidget.h"

AExitDoorSwitch::AExitDoorSwitch()
	: bDoorOpened(false), SwitchCurrentRotation(FRotator(45.0f, 0.0f, 0.0f)), bFuseFound(false)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	/* Scene Root */
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	RootComponent->Mobility = EComponentMobility::Static;

	/* Switch Base */
	SwitchBaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch Base Mesh Component"));
	SwitchBaseMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	SwitchBaseMeshComp->SetStaticMesh(CubeMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> WhiteMaterialAsset(TEXT("Material'/Game/Materials/M_Flat_White.M_Flat_White'"));
	SwitchBaseMeshComp->SetMaterial(0, WhiteMaterialAsset.Object);

	SwitchBaseMeshComp->Mobility = EComponentMobility::Static;
	SwitchBaseMeshComp->SetRelativeScale3D(FVector(0.125f, 1.0f, 1.0f));
	SwitchBaseMeshComp->SetGenerateOverlapEvents(false);

	/* Siwtch Handle */
	SwitchMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Switch Handle Mesh Component"));
	SwitchMeshComp->SetupAttachment(RootComponent);

	SwitchMeshComp->SetStaticMesh(CubeMeshAsset.Object);
	SwitchMeshComp->SetMaterial(0, WhiteMaterialAsset.Object);

	SwitchMeshComp->Mobility = EComponentMobility::Movable;
	SwitchMeshComp->SetRelativeScale3D(FVector(0.0625f, 0.25f, 1.0f));
	SwitchMeshComp->SetRelativeRotation(SwitchCurrentRotation);
	SwitchMeshComp->SetGenerateOverlapEvents(false);

	/* Wiget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Exit Door Switch Widget"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ItemWidgetComp->SetGenerateOverlapEvents(false);
	ItemWidgetComp->SetVisibility(false);
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void AExitDoorSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UIs/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("Exit Door Switch"));
	ItemWidget->DescriptionText->SetText(FText::FromString("A Switch to Open the Exit Door.\n\nNote: A Fuze is Required to Open it.\n\nPress \"E\" to Open the Door"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void AExitDoorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SwitchCurrentRotation.Pitch += DeltaTime * 256.0f;

	if (135.0f - SwitchCurrentRotation.Pitch < 1.0f)
		SetActorTickEnabled(false);
	else
		SwitchMeshComp->SetRelativeRotation(SwitchCurrentRotation);
}

void AExitDoorSwitch::Interact()
{
	if (!bDoorOpened) {
		if (bFuseFound) {
			bDoorOpened = true;
			SetActorTickEnabled(true);
			ExitDoor->Open();
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "The Exit Door is Opened");
		} else {
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, "Find and Place the Fuse in the Fuse Box to Activate the Switch");
		}
	} 
}
