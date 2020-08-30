#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "FirstAidKit.generated.h"

UCLASS()
class ASSIGNMENT_1_API AFirstAidKit : public AActor, public IInteractable
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent *FirstAidKitMeshComp;

public:
	AFirstAidKit();
	void BeginPlay() override;

	void Interact() override;
};
