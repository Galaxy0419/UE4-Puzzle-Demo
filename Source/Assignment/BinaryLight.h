#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "BinaryLight.generated.h"

UCLASS()
class ASSIGNMENT_API ABinaryLight : public AActor
{
	GENERATED_BODY()

private:
	UMaterial *OnMaterial;
	UMaterial *OffMaterial;
	UStaticMeshComponent *LightMeshComp;

public:
	ABinaryLight();

	bool bLightOn;

	FORCEINLINE bool ToggleLight() {
		bLightOn = !bLightOn;
		LightMeshComp->SetMaterial(0, bLightOn ? OnMaterial : OffMaterial);
		return bLightOn;
	};
};
