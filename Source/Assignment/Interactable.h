#pragma once

#include "Components/WidgetComponent.h"
#include "UObject/Interface.h"

#include "Interactable.generated.h"

class APlayerCharacter;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ASSIGNMENT_API IInteractable
{
	GENERATED_BODY()
	
public:
	UWidgetComponent *ItemWidgetComp;

	virtual void Interact(APlayerCharacter *Player) PURE_VIRTUAL(&IInteractable::Interact,);
};
