#pragma once

#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

#include "GameOverUserWidget.generated.h"

UCLASS(meta = (DisableNativeTick))
class ASSIGNMENT_API UGameOverUserWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock *WinLostText;
};
