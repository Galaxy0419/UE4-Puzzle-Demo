#pragma once

#include "Blueprint/UserWidget.h"
#include "Engine/LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"

#include "BinaryLight.h"
#include "SimpleDoor.h"
#include "GameOverUserWidget.h"
#include "PlayerCharacter.h"

#include "MainLevelScriptActor.generated.h"

#define FOG_DAMAGE	-0.0625f

UCLASS()
class ASSIGNMENT_API AMainLevelScriptActor final : public ALevelScriptActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UUserWidget *MenuWBP;

	UPROPERTY()
	UUserWidget *PauseWBP;

	UPROPERTY()
	UGameOverUserWidget *GameOverWBP;

	bool bBinaryDoorOpened;

	UPROPERTY(EditAnywhere)
	ASimpleDoor *BinarySimpleDoor;

	UPROPERTY(EditAnywhere)
	TArray<ABinaryLight *> BinaryLights;

	FTimerHandle HealthLossTimerHandle;
	FORCEINLINE void LossHealth() { MainCharacter->TakeDamage(FOG_DAMAGE, FDamageEvent(), nullptr, this); };

	void UpdateGamePlayState(EGamePlayState State) const;

public:
	AMainLevelScriptActor();
	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	APlayerCharacter *MainCharacter;

	void UpdateBinaryLight(uint8 Mask);
};
