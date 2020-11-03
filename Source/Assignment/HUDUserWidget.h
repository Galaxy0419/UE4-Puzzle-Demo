#pragma once

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

#include "HUDUserWidget.generated.h"

UCLASS(meta = (DisableNativeTick))
class ASSIGNMENT_API UHUDUserWidget final : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar *HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *FirstAidKitNumberText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *KeyNumberText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *FuseNumberText;
};
