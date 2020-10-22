#include "FuseBox.h"

#include "Kismet/GameplayStatics.h"

#include "ItemUserWidget.h"
#include "PlayerCharacter.h"

AFuseBox::AFuseBox()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Scene Root */
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	RootComponent->Mobility = EComponentMobility::Static;

	/* Fuse Box */
	FuseBoxMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fuse Box Mesh Component"));
	FuseBoxMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		FuseBoxMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	FuseBoxMeshComp->SetStaticMesh(FuseBoxMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial>
		FuseBoxMaterialAsset(TEXT("Material'/Game/Materials/M_Flat_White.M_Flat_White'"));
	FuseBoxMeshComp->SetMaterial(0, FuseBoxMaterialAsset.Object);

	FuseBoxMeshComp->Mobility = EComponentMobility::Static;
	FuseBoxMeshComp->SetRelativeScale3D(FVector(0.125f, 1.0f, 1.0f));
	FuseBoxMeshComp->SetGenerateOverlapEvents(false);
	
	/* Fuse */
	FuseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fuse Mesh Component"));
	FuseMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		FuseMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	FuseMeshComp->SetStaticMesh(FuseMeshAsset.Object);

	FuseMeshComp->Mobility = EComponentMobility::Static;
	FuseMeshComp->SetMaterial(0, FuseBoxMaterialAsset.Object);
	FuseMeshComp->SetRelativeLocation(FVector(-16.0f, 20.0f, 0.0f));
	FuseMeshComp->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.8f));
	FuseMeshComp->SetGenerateOverlapEvents(false);
	FuseMeshComp->SetVisibility(false);

	/* Fuse Box Light */
	FuseBoxLightMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fuse Box Light Mesh Component"));
	FuseBoxLightMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial>
		FuseBoxLightOnMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_On.M_Switch_On'"));
	OnMaterial = FuseBoxLightOnMaterialAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>
		FuseBoxLightOffMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_Off.M_Switch_Off'"));
	OffMaterial = FuseBoxLightOffMaterialAsset.Object;

	FuseBoxLightMeshComp->Mobility = EComponentMobility::Static;
	FuseBoxLightMeshComp->SetStaticMesh(FuseBoxMeshAsset.Object);
	FuseBoxLightMeshComp->SetRelativeLocation(FVector(-10.0f, -30.0f, 0.0f));
	FuseBoxLightMeshComp->SetRelativeScale3D(FVector(0.0625f, 0.25f, 0.25f));
	FuseBoxLightMeshComp->SetGenerateOverlapEvents(false);
	FuseBoxLightMeshComp->SetMaterial(0, FuseBoxLightOffMaterialAsset.Object);

	/* Spark Niagara System */
	SparkNiagComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Spark Niagara System Component"));
	SparkNiagComp->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>
		SparkNiagSysAsset(TEXT("NiagaraSystem'/Game/Particle_Systems/NS_Spark.NS_Spark'"));
	SparkNiagComp->SetAsset(SparkNiagSysAsset.Object);
	
	SparkNiagComp->Mobility = EComponentMobility::Static;
	SparkNiagComp->SetRelativeLocation(FVector(-8.0f, -32.0f, 16.0f));
	SparkNiagComp->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));

	/* Humming Sound */
	HummingAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Humming Sound Audio Component"));
	HummingAudioComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundWave> HummingSoundAsset(TEXT("SoundWave'/Game/Audios/SW_Humming.SW_Humming'"));
	HummingAudioComp->SetSound(HummingSoundAsset.Object);

	/* Widget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Fuse Box Widget"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ItemWidgetComp->SetGenerateOverlapEvents(false);
	ItemWidgetComp->SetVisibility(false);
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void AFuseBox::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(),
		nullptr, TEXT("WidgetBlueprint'/Game/UIs/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("Fuse Box"));
	ItemWidget->DescriptionText->SetText(FText::FromString(
		"A Broken Fuse Box to Unlock the Exit Door.\n\nNote: A Fuze is Required to Open it.\n\nPress \"E\" to Place the Fuse"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void AFuseBox::Interact(APlayerCharacter *Player)
{
	if (Player->FuseNumber > 0) {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "Door Switch is Activated");
		FuseMeshComp->SetVisibility(true);
		FuseBoxLightMeshComp->SetMaterial(0, OnMaterial);
		ExitDoorSwitch->bFuseFound = true;
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, "A Fuse is Required to Activate Door Switch");
	}
}
