#pragma once

#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Niagara/Public/NiagaraComponent.h"

#include "Interactable.h"
#include "ExitDoorSwitch.h"

#include "FuseBox.generated.h"

UCLASS()
class ASSIGNMENT_API AFuseBox final : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	bool bOpened;

	UPROPERTY(EditAnywhere)
	AExitDoorSwitch *ExitDoorSwitch;

	UMaterial *OnMaterial;
	UMaterial *OffMaterial;
	UStaticMeshComponent *FuseBoxMeshComp;
	UStaticMeshComponent *FuseMeshComp;
	UStaticMeshComponent *FuseBoxLightMeshComp;
	UNiagaraComponent *SparkNiagComp;
	UAudioComponent *HummingAudioComp;

public:
	AFuseBox();
	void BeginPlay() override;

	void Interact(APlayerCharacter *Player) override;
};
