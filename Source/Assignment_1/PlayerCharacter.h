#pragma once

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "TimerManager.h"

#include "HUDUserWidget.h"
#include "GameOverUserWidget.h"

#include "PlayerCharacter.generated.h"

#define FOG_DAMAGE	-0.0625f

UCLASS()
class ASSIGNMENT_1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	float Health;
	FTimerHandle HealthLossTimerHandle;

	UCameraComponent *TPCameraComp;
	USpotLightComponent *FlashLightComp;
	USpringArmComponent *SpringArmComp;

	UPROPERTY()
	UHUDUserWidget *HUDWBP;

	UPROPERTY()
	UUserWidget *PauseWBP;

	UPROPERTY()
	UGameOverUserWidget *GameOverWBP;

	void Pause();
	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); };
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); };
	void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

	FORCEINLINE void LossHealth() { UpdateHealth(FOG_DAMAGE); };

public:
	APlayerCharacter();
	void BeginPlay() override;

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	bool UpdateHealth(float DeltaHealth);
};
