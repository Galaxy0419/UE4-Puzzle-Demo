#pragma once

#include "Components/WidgetComponent.h"
#include "UObject/Interface.h"

#include "Interactable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ASSIGNMENT_1_API IInteractable
{
	GENERATED_BODY()
	
public:
	UWidgetComponent *ItemWidgetComp;

	virtual void Interact() PURE_VIRTUAL(&IInteractable::Interact,);
};
