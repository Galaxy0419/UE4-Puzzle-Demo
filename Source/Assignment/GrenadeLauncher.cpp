#include "GrenadeLauncher.h"

#include "Kismet/GameplayStatics.h"

#include "ItemUserWidget.h"
#include "StunGrenade.h"
#include "PlayerCharacter.h"

static const FVector MuzzleLocation(0.0f, 55.0f, 12.0f);

AGrenadeLauncher::AGrenadeLauncher()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Grenade Launcher Skeletal Mesh Component */
	GrenadeLauncherMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Launcher Root Static Mesh Component"));
	RootComponent = GrenadeLauncherMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		GrenadeLauncherAsset(TEXT("StaticMesh'/Game/Mannequin/Weapon/Mesh/SM_GrenadeLauncher.SM_GrenadeLauncher'"));
	GrenadeLauncherMeshComp->SetStaticMesh(GrenadeLauncherAsset.Object);
	
	/* Muzzle Smoke Niagara Component */
	FireNiagComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Weapon Muzzle Smoke Niagara Paricle System"));
	FireNiagComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>
        MuzzleSmokeAsset(TEXT("NiagaraSystem'/Game/Particle_Systems/NS_MuzzleSmoke.NS_MuzzleSmoke'"));
	FireNiagComp->SetAsset(MuzzleSmokeAsset.Object);

	FireNiagComp->bAutoActivate = false;
	FireNiagComp->SetRelativeLocation(MuzzleLocation);

	/* Fire Sound Component */
	FireAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Fire Audio Component"));
	FireAudioComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundWave>
		FireAudioAsset(TEXT("SoundWave'/Game/Audios/SW_GrenadeLauncher.SW_GrenadeLauncher'"));
	FireAudioComp->SetSound(FireAudioAsset.Object);

	FireAudioComp->bAutoActivate = false;
	FireAudioComp->SetRelativeLocation(MuzzleLocation);
	
	/* Widget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Grenade Launcher"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->SetGenerateOverlapEvents(false);
	ItemWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	ItemWidgetComp->SetVisibility(false);
	ItemWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
}

void AGrenadeLauncher::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widget */
	UClass *ItemWidgetClass = StaticLoadClass(UItemUserWidget::StaticClass(),
        nullptr, TEXT("WidgetBlueprint'/Game/UIs/WBP_Item_Description.WBP_Item_Description_C'"));
	UItemUserWidget *ItemWidget = CreateWidget<UItemUserWidget>(GetWorld(), ItemWidgetClass);

	ItemWidget->TitleText->SetText(FText::FromString("Stun Grenade Launcher"));
	ItemWidget->DescriptionText->SetText(FText::FromString(
        "\nA Grenade Launcher shoot out stun rounds to incapacitate enemies.\n\nPress \"E\" to Pick Up"));

	ItemWidgetComp->SetWidget(ItemWidget);
}

void AGrenadeLauncher::Interact(APlayerCharacter *Player)
{
	SetActorEnableCollision(false);
	Player->GrenadeLauncher = this;
	AttachToComponent(Player->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "GripPoint");
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "You Found the Stun Weapon!");
}

void AGrenadeLauncher::Fire(const FVector& Direction)
{
	/* Shoot Grenade */
	AStunGrenade *Grenade = GetWorld()->SpawnActorDeferred<AStunGrenade>(AStunGrenade::StaticClass(), FTransform(), this);
	Grenade->ForwardVector = Direction;
	UGameplayStatics::FinishSpawningActor(Grenade, FTransform(FireNiagComp->GetComponentToWorld().GetLocation()));
	
	/* Play Particle Effects */
	FireNiagComp->Activate(true);

	/* Play Fire Sound */
	FireAudioComp->Play();
}
