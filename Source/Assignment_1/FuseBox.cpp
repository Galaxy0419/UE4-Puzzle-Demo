#include "FuseBox.h"

AFuseBox::AFuseBox()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Scene Root */
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));
	RootComponent->Mobility = EComponentMobility::Static;

	/* Fuse Box */
	FuseBoxMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fuse Box Mesh Component"));
	FuseBoxMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FuseBoxMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	FuseBoxMeshComp->SetStaticMesh(FuseBoxMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> FuseBoxMaterialAsset(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	FuseBoxMeshComp->SetMaterial(0, FuseBoxMaterialAsset.Object);

	FuseBoxMeshComp->Mobility = EComponentMobility::Static;
	FuseBoxMeshComp->SetRelativeScale3D(FVector(0.125f, 1.0f, 1.0f));
	FuseBoxMeshComp->SetCollisionProfileName("Trigger");
	
	/* Fuse */
	FuseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fuse Mesh Component"));
	FuseMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FuseMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	FuseMeshComp->SetStaticMesh(FuseMeshAsset.Object);

	FuseMeshComp->Mobility = EComponentMobility::Static;
	FuseMeshComp->SetMaterial(0, FuseBoxMaterialAsset.Object);
	FuseMeshComp->SetRelativeLocation(FVector(-16.0f, 20.0f, 0.0f));
	FuseMeshComp->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.8f));
	FuseMeshComp->SetVisibility(false);

	/* Fuse Box Light */
	FuseBoxLightMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fuse Box Light Mesh Component"));
	FuseBoxLightMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> FuseBoxLightOnMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_On.M_Switch_On'"));
	OnMaterial = FuseBoxLightOnMaterialAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial> FuseBoxLightOffMaterialAsset(TEXT("Material'/Game/Materials/M_Switch_Off.M_Switch_Off'"));
	OffMaterial = FuseBoxLightOffMaterialAsset.Object;

	FuseBoxLightMeshComp->Mobility = EComponentMobility::Static;
	FuseBoxLightMeshComp->SetStaticMesh(FuseBoxMeshAsset.Object);
	FuseBoxLightMeshComp->SetRelativeLocation(FVector(-10.0f, -30.0f, 0.0f));
	FuseBoxLightMeshComp->SetRelativeScale3D(FVector(0.0625f, 0.25f, 0.25f));
	FuseBoxLightMeshComp->SetMaterial(0, FuseBoxLightOffMaterialAsset.Object);

	/* On Actor Overlap */
	OnActorBeginOverlap.AddDynamic(this, &AFuseBox::OnFuseBoxBeginOverlap);
}

void AFuseBox::OnFuseBoxBeginOverlap(AActor *OverlappedActor, AActor *OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "Exit Door is Opened");
	FuseMeshComp->SetVisibility(true);
	FuseBoxLightMeshComp->SetMaterial(0, OnMaterial);
	ExitDoor->SetActorTickEnabled(true);
}