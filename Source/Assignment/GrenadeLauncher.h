#pragma once

#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"

#include "Interactable.h"

#include "GrenadeLauncher.generated.h"

UCLASS()
class ASSIGNMENT_API AGrenadeLauncher : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	UStaticMeshComponent *GrenadeLauncherMeshComp;
	UAudioComponent *FireAudioComp;
	UNiagaraComponent *FireNiagComp;
	
public:
	AGrenadeLauncher();
	void BeginPlay() override;

	void Interact(APlayerCharacter *Player) override;
	void Fire(const FVector& Direction);
};
