#pragma once

#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"

#include "BinarySwitch.generated.h"

UENUM(meta = (Bitflags))
enum class ELightMask : uint8
{
	Light1,
	Light2,
	Light3
};
ENUM_CLASS_FLAGS(ELightMask)

UCLASS()
class ASSIGNMENT_API ABinarySwitch final : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	UStaticMeshComponent *SwitchMeshComp;
	UAudioComponent *ClickAudioComp;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ELightMask"), DisplayName = "Lights to Trun On")
	uint8 LightMasks;

public:	
	ABinarySwitch();
	void BeginPlay() override;

	void Interact() override;
};
