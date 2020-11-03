#pragma once

#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "FirstAidKit.generated.h"

UCLASS()
class ASSIGNMENT_API AFirstAidKit final : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	UStaticMeshComponent *FirstAidKitMeshComp;

public:
	AFirstAidKit();
	void BeginPlay() override;

	void Interact(APlayerCharacter *Player) override;
};
