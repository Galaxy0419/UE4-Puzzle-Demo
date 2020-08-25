#include "MainLevelScriptActor.h"

#include "Kismet/GameplayStatics.h"

AMainLevelScriptActor::AMainLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	/* Create Menu Widget */
	UClass *MenuWBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Menu.WBP_Menu_C'"));
	MenuWBP = CreateWidget<UUserWidget>(GetWorld(), MenuWBPClass);
	MenuWBP->AddToViewport(1);

	/* Show Mouse Cursor */
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

	/* Pause The Game First */
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
