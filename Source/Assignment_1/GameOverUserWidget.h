#pragma once

#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

#include "GameOverUserWidget.generated.h"

UCLASS()
class ASSIGNMENT_1_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock *WinLostText;
};
