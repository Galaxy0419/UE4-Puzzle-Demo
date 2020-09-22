#pragma once

#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

#include "ItemUserWidget.generated.h"

UCLASS(meta = (DisableNativeTick))
class ASSIGNMENT_API UItemUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock *TitleText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock *DescriptionText;
};
