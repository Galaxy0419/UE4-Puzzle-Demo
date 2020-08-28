#pragma once

#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"

#include "RemoteSwitch.generated.h"

DECLARE_EVENT(ARemoteSwitch, FOnSwitchToggle);

UCLASS()
class ASSIGNMENT_1_API ARemoteSwitch : public AActor
{
	GENERATED_BODY()
	
private:
	bool bOpened;

	UMaterial *OnMaterial;
	UMaterial *OffMaterial;
	UStaticMeshComponent *SwitchMeshComp;

	UFUNCTION()
	void OnSwitchBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

public:
	ARemoteSwitch();

	FOnSwitchToggle OnSwitchToggle;
};
