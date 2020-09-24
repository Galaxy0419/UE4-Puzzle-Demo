#include "AICharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"

#include "PlayerCharacter.h"

AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Capsule Component */
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AAICharacter::OnCapsuleHit);

	/* Set Skeletal Mesh */
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterSKMeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	GetMesh()->SetSkeletalMesh(CharacterSKMeshAsset.Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -94.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	/* Set Material */
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>
		EnemyBodyAsset(TEXT("MaterialInstanceConstant'/Game/Mannequin/Character/Materials/MI_Enemy_Body.MI_Enemy_Body'"));
	GetMesh()->SetMaterial(0, EnemyBodyAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>
		EnemyLogoAsset(TEXT("MaterialInstanceConstant'/Game/Mannequin/Character/Materials/MI_Enemy_Logo.MI_Enemy_Logo'"));
	GetMesh()->SetMaterial(1, EnemyLogoAsset.Object);
	

	/* Set Animation */
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnumBPClass(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
	GetMesh()->SetAnimInstanceClass(AnumBPClass.Class);

	/* AI Movement */
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 5.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	/* AI Controller */
	AutoReceiveInput = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::Disabled;
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	/* Create AI Controller Instance */
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.OverrideLevel = GetLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;
	
	AAIController* ControllerInstance = GetWorld()->SpawnActor<AAIController>(
		AIControllerClassOverride, GetActorLocation(), GetActorRotation(), SpawnInfo);
	ControllerInstance->Possess(this);

	ControllerInstance->MoveToLocation(GetActorLocation());
}

void AAICharacter::OnCapsuleHit(UPrimitiveComponent *HitComponent,
	AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	if (Cast<APlayerCharacter>(OtherActor))
		OtherActor->TakeDamage(-0.01f, FDamageEvent(), nullptr, this);
}
