#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "BinaryLight.h"
#include "SimpleDoor.h"
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
class ASSIGNMENT_1_API ABinarySwitch : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	UStaticMeshComponent *SwitchMeshComp;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ELightMask"), DisplayName = "Lights to Trun On")
	uint8 LightMasks;

public:	
	ABinarySwitch();
	void BeginPlay() override;

	void Interact() override;
};
