#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "Fuse.generated.h"

UCLASS()
class ASSIGNMENT_1_API AFuse : public AActor, public IInteractable
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent *FuseMeshComp;

public:
	AFuse();
	void BeginPlay() override;

	void Interact() override;
};
