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
	Light3,
	LightMax
};
ENUM_CLASS_FLAGS(ELightMask)

UCLASS()
class ASSIGNMENT_1_API ABinarySwitch : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	bool bOpend;

	UPROPERTY(EditAnywhere)
	ASimpleDoor *DoorToOpen;

	UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "ELightMask"), DisplayName = "Lights to Trun On")
	uint8 LightMasks;

	UPROPERTY(EditAnywhere)
	TArray<ABinaryLight *> BinaryLights;

	UStaticMeshComponent *SwitchMeshComp;

public:	
	ABinarySwitch();
	void BeginPlay() override;

	void Interact() override;
};
