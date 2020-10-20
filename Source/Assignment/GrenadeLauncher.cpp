#include "GrenadeLauncher.h"

#include "Kismet/GameplayStatics.h"

#include "ItemUserWidget.h"
#include "PlayerCharacter.h"

AGrenadeLauncher::AGrenadeLauncher()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Grenade Launcher Skeletal Mesh Component */
	GrenadeLauncherMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Launcher Root Static Mesh Component"));
	RootComponent = GrenadeLauncherMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		GrenadeLauncherAsset(TEXT("StaticMesh'/Game/Mannequin/Weapon/Mesh/SM_GrenadeLauncher.SM_GrenadeLauncher'"));
	GrenadeLauncherMeshComp->SetStaticMesh(GrenadeLauncherAsset.Object);
	GrenadeLauncherMeshComp->Mobility = EComponentMobility::Static;

	/* Widget Component */
	ItemWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Grenade Launcher"));
	ItemWidgetComp->SetupAttachment(RootComponent);

	ItemWidgetComp->Mobility = EComponentMobility::Static;
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

void AGrenadeLauncher::Interact()
{
	Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->EquipWeapon();
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, "You Found the Stun Weapon!");
	Destroy();
}

