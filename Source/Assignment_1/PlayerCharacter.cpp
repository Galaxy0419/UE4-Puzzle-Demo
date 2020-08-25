#include "PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"

#include "Interactable.h"

APlayerCharacter::APlayerCharacter()
	: Health(1.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	/* Capsule Component */
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnCapsuleBeginOverlap);

	/* Set Skeletal Mesh */
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterSKMeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(CharacterSKMeshAsset.Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -94.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	/* Set Animation */
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnumBPClass(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
	GetMesh()->SetAnimInstanceClass(AnumBPClass.Class);

	/* Spring Arm Component */
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(RootComponent);

	SpringArmComp->TargetArmLength = 256.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));

	/* Camera Component */
	TPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera Component"));
	TPCameraComp->SetupAttachment(SpringArmComp);

	static ConstructorHelpers::FObjectFinder<UMaterial> FogPPMAsset(TEXT("Material'/Game/Materials/PPM_Fog.PPM_Fog'"));
	TPCameraComp->PostProcessSettings.WeightedBlendables.Array.Add(FWeightedBlendable(1.0f, FogPPMAsset.Object));

	/* Flash Light Component */
	FlashLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flash Light Component"));
	FlashLightComp->SetupAttachment(SpringArmComp);

	FlashLightComp->SetRelativeLocation(FVector(16.0f, 0.0f, 32.0f));
	FlashLightComp->Intensity = 16384.0f;
	FlashLightComp->AttenuationRadius = 8192.0f;
	FlashLightComp->InnerConeAngle = 16.0f;
	FlashLightComp->OuterConeAngle = 32.0f;

	/* Posses by Player */
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoPossessAI = EAutoPossessAI::Disabled;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widgets */
	UClass *HUDWBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_HUD.WBP_HUD_C'"));
	HUDWBP = CreateWidget<UHUDUserWidget>(GetWorld(), HUDWBPClass);
	HUDWBP->AddToViewport(0);

	UClass *PauseWBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Pause.WBP_Pause_C'"));
	PauseWBP = CreateWidget<UUserWidget>(GetWorld(), PauseWBPClass);
	
	UClass *GameOverWBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Game_Over.WBP_Game_Over_C'"));
	GameOverWBP = CreateWidget<UGameOverUserWidget>(GetWorld(), GameOverWBPClass);

	/* Set Timer for Automatic Health Loss */
	GetWorldTimerManager().SetTimer(HealthLossTimerHandle, this, &APlayerCharacter::LossHealth, 4.0f, true);
}

void APlayerCharacter::Pause()
{
	PauseWBP->AddToViewport(1);
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::Pause).bExecuteWhenPaused = true;
}

void APlayerCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		Cast<IInteractable>(OtherActor)->Interact();
}

bool APlayerCharacter::UpdateHealth(float DeltaHealth)
{
	float NewHealth = Health + DeltaHealth;

	if (NewHealth > 0.0f) {
		if (NewHealth > 1.0f)
			NewHealth = 1.0f;
		HUDWBP->HealthProgressBar->SetPercent(Health = NewHealth);
		return true;
	} else if (NewHealth <= 0.0f) {
		GameOverWBP->WinLostText->SetText(FText::FromString("You lost and died in the fog!"));
		GameOverWBP->AddToViewport(1);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	return false;
}
