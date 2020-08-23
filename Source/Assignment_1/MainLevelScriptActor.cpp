#include "MainLevelScriptActor.h"

AMainLevelScriptActor::AMainLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	/* Show Menu Widget */
	UClass *MenuWBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Menu.WBP_Menu_C'"));
	MenuWBP = CreateWidget<UUserWidget>(GetWorld(), MenuWBPClass);
	MenuWBP->AddToViewport();

	/* Show Mouse Cursor */
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
}
