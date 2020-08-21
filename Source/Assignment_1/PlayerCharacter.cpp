#include "PlayerCharacter.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Capsule Component */
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);
	
	/* Set Skeletal Mesh */
	ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterSKMeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(CharacterSKMeshAsset.Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -94.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	/* Set Animation */
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FClassFinder<UAnimInstance> AnumBPClass(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
	GetMesh()->SetAnimInstanceClass(AnumBPClass.Class);

	/* Spring Arm Component */
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->SetupAttachment(RootComponent);

	SpringArmComp->TargetArmLength = 256.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	/* Camera Component */
	TPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera Component"));
	TPCameraComp->SetupAttachment(SpringArmComp);

	/* Posses by Player */
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoPossessAI = EAutoPossessAI::Disabled;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}