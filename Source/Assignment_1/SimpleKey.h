#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"
#include "SimpleDoor.h"

#include "SimpleKey.generated.h"

UCLASS()
class ASSIGNMENT_1_API ASimpleKey : public AActor, public IInteractable
{
	GENERATED_BODY()
	
private:
	UStaticMeshComponent *SimpleKeyMeshComp;

	UPROPERTY(EditAnywhere)
	ASimpleDoor *SimpleDoorToUnlock;

public:
	ASimpleKey();

	UFUNCTION()
	void OnKeyBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void Interact() override;
};
