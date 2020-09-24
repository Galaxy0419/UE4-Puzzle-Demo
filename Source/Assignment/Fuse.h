#pragma once

#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "Fuse.generated.h"

UCLASS()
class ASSIGNMENT_API AFuse final : public AActor, public IInteractable
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent *FuseMeshComp;

public:
	AFuse();
	void BeginPlay() override;

	void Interact() override;
};
