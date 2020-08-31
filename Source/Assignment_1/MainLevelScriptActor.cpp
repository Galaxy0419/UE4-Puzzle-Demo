#include "MainLevelScriptActor.h"

AMainLevelScriptActor::AMainLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	/* Bind Events */
	MainCharacter->OnGamePlayStateChange.AddUObject(this, &AMainLevelScriptActor::UpdateGamePlayState);

	/* Set Timer for Automatic Health Loss */
	GetWorldTimerManager().SetTimer(HealthLossTimerHandle, this, &AMainLevelScriptActor::LossHealth, 4.0f, true);

	/* Create Widgets */
	UClass *MenuWBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Menu.WBP_Menu_C'"));
	MenuWBP = CreateWidget<UUserWidget>(GetWorld(), MenuWBPClass);
	MenuWBP->AddToViewport(1);

	UClass *PauseWBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Pause.WBP_Pause_C'"));
	PauseWBP = CreateWidget<UUserWidget>(GetWorld(), PauseWBPClass);

	UClass *GameOverWBPClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/WBP_Game_Over.WBP_Game_Over_C'"));
	GameOverWBP = CreateWidget<UGameOverUserWidget>(GetWorld(), GameOverWBPClass);

	/* Show Mouse Cursor */
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());

	/* Pause The Game First */
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMainLevelScriptActor::UpdateGamePlayState(EGamePlayState State)
{
	switch (State) {
		case EGamePlayState::Playing:
			return;
		case EGamePlayState::Paused:
			PauseWBP->AddToViewport(1);
			break;
		case EGamePlayState::Dead:
			GameOverWBP->WinLostText->SetText(FText::FromString("\nYou lost and died in the fog!"));
			GameOverWBP->AddToViewport(1);
			break;
		case EGamePlayState::Won:
			GameOverWBP->WinLostText->SetText(FText::FromString("               Congratulations!\n\nYou escaped from the poison fog!"));
			GameOverWBP->AddToViewport(1);
			break;
		default:
			return;
	}

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
