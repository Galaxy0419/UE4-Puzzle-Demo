#pragma once

#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class ASSIGNMENT_1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	USpringArmComponent *SpringArmComp;
	UCameraComponent *TPCameraComp;
	USpotLightComponent *FlashLightComp;

public:
	APlayerCharacter();
	void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); };
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); };
};
