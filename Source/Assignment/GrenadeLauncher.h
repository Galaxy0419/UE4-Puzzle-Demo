#pragma once

#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "GrenadeLauncher.generated.h"

UCLASS()
class ASSIGNMENT_API AGrenadeLauncher : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	UStaticMeshComponent *GrenadeLauncherMeshComp;
	
public:
	AGrenadeLauncher();
	void BeginPlay() override;

	void Interact() override;
};
