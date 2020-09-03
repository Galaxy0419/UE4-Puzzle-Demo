#pragma once

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "TimerManager.h"

#include "Interactable.h"
#include "HUDUserWidget.h"

#include "PlayerCharacter.generated.h"

enum class EGamePlayState : uint8 {
	Playing,
	Paused,
	Dead,
	Won
};

DECLARE_EVENT_OneParam(APlayerCharacter, FOnGamePlayStateChange, EGamePlayState);

UCLASS()
class ASSIGNMENT_1_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UCameraComponent *TPCameraComp;
	USpotLightComponent *FlashLightComp;
	USpringArmComponent *SpringArmComp;

	FHitResult LineTaceHitRes;
	FTransform TPCamTranform;
	FVector TraceStart, TraceEnd;
	IInteractable *InteractableItem;

	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); };
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); };
	FORCEINLINE void Pause() { OnGamePlayStateChange.Broadcast(EGamePlayState::Paused); };
	FORCEINLINE void Interact() { if (InteractableItem) InteractableItem->Interact(); };
	void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

public:
	APlayerCharacter();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	float Health;
	uint8 FirstAidKitNumber;
	uint8 KeyNumber;
	uint8 FuseNumber;
	FOnGamePlayStateChange OnGamePlayStateChange;

	UPROPERTY()
	UHUDUserWidget *HUDWBP;

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnCharacterTakeDamage(AActor *DamagedActor, float Damage,
		const UDamageType *DamageType, AController *InstigatedBy, AActor *DamageCauser);
};
