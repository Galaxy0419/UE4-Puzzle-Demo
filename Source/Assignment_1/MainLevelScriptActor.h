#pragma once

#include "Blueprint/UserWidget.h"
#include "Engine/LevelScriptActor.h"

#include "MainLevelScriptActor.generated.h"

UCLASS()
class ASSIGNMENT_1_API AMainLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
private:
	UUserWidget *MenuWBP;
	UUserWidget *HUDWBP;
	UUserWidget *EndGameWBP;

public:
	AMainLevelScriptActor();
	void BeginPlay() override;
};
