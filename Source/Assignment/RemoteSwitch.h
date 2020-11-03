#pragma once

#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "RemoteSwitch.generated.h"

DECLARE_EVENT(ARemoteSwitch, FOnSwitchToggle);

UCLASS()
class ASSIGNMENT_API ARemoteSwitch final : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	bool bOpened;

	UMaterial *OnMaterial;
	UMaterial *OffMaterial;
	UStaticMeshComponent *SwitchMeshComp;

public:
	ARemoteSwitch();
	void BeginPlay() override;

	FOnSwitchToggle OnSwitchToggle;

	void Interact(APlayerCharacter *Player) override;
};
