#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "HUDUserWidget.generated.h"

UCLASS(meta = (DisableNativeTick))
class ASSIGNMENT_1_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar *HealthProgressBar;
};
