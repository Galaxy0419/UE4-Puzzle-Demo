#pragma once

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class ASSIGNMENT_1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UCameraComponent *TPCameraComp;
	USpotLightComponent *FlashLightComp;
	USpringArmComponent *SpringArmComp;

	UPROPERTY()
	UUserWidget *HUDWBP;

	UPROPERTY()
	UUserWidget *PauseWBP;

public:
	APlayerCharacter();
	void BeginPlay() override;
	
	void Pause();
	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); };
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); };
	void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;
};
