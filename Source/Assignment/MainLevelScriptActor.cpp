#include "MainLevelScriptActor.h"

AMainLevelScriptActor::AMainLevelScriptActor()
	: bBinaryDoorOpened(false)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	/* Create Widgets */
	UClass *PauseWBPClass = StaticLoadClass(UUserWidget::StaticClass(),
		nullptr, TEXT("WidgetBlueprint'/Game/UIs/WBP_Pause.WBP_Pause_C'"));
	PauseWBP = CreateWidget<UUserWidget>(GetWorld(), PauseWBPClass);

	UClass *GameOverWBPClass = StaticLoadClass(UUserWidget::StaticClass(),
		nullptr, TEXT("WidgetBlueprint'/Game/UIs/WBP_Game_Over.WBP_Game_Over_C'"));
	GameOverWBP = CreateWidget<UGameOverUserWidget>(GetWorld(), GameOverWBPClass);

	/* Bind Events */
	MainCharacter->OnGamePlayStateChange.AddUObject(this, &AMainLevelScriptActor::UpdateGamePlayState);

	/* Disable Player Input When Playing Intro Sequence */
	MainCharacter->DisableInput(Cast<APlayerController>(MainCharacter->GetController()));

	/* Load Sequence Asset */
	ALevelSequenceActor *SequencePlayerActor;
	ULevelSequence *IntroSequenceAsset = LoadObject<ULevelSequence>(this, TEXT("LevelSequence'/Game/Cinematics/Master.Master'"));
	IntroSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(), IntroSequenceAsset, FMovieSceneSequencePlaybackSettings(), SequencePlayerActor);

	/* Bind Sequence Event */
	IntroSequencePlayer->OnFinished.AddDynamic(this, &AMainLevelScriptActor::OnIntroFinished);

	/* Play the Sequence */
	IntroSequencePlayer->Play();
}

void AMainLevelScriptActor::UpdateBinaryLight(uint8 Mask)
{
	if (!bBinaryDoorOpened) {
		bool bAllOn = true;

		for (uint8 i = 0; i < 3; i++) {
			if (Mask & (1 << i)) {
				if (!(BinaryLights[i]->ToggleLight()))
					bAllOn = false;
			} else if (!(BinaryLights[i]->bLightOn)) {
				bAllOn = false;
			}
		}

		if (bAllOn) {
			bBinaryDoorOpened = true;
			BinarySimpleDoor->Open();
			LaserCutter->SetActorTickEnabled(true);
		}
	}
}

void AMainLevelScriptActor::OnIntroFinished()
{
	/* Set Timer for Automatic Health Loss */
	GetWorldTimerManager().SetTimer(HealthLossTimerHandle, this, &AMainLevelScriptActor::LossHealth, 4.0f, true);

	/* Add HUD to Viewport */
	MainCharacter->HUDWBP->AddToViewport(0);

	/* Enable Character Input */
	MainCharacter->EnableInput(Cast<APlayerController>(MainCharacter->GetController()));
}

void AMainLevelScriptActor::UpdateGamePlayState(EGamePlayState State) const
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
