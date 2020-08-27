#pragma once

#include "Blueprint/UserWidget.h"
#include "Engine/LevelScriptActor.h"

#include "GameOverUserWidget.h"
#include "PlayerCharacter.h"

#include "MainLevelScriptActor.generated.h"

UCLASS()
class ASSIGNMENT_1_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UUserWidget *MenuWBP;

	UPROPERTY()
	UUserWidget *PauseWBP;

	UPROPERTY()
	UGameOverUserWidget *GameOverWBP;

	UPROPERTY(EditAnywhere)
	APlayerCharacter *MainCharacter;

	void UpdateGamePlayState(EGamePlayState State);

public:
	AMainLevelScriptActor();
	void BeginPlay() override;
};
