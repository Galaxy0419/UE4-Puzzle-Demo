#pragma once

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "Interactable.h"
#include "GrenadeLauncher.h"
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
class ASSIGNMENT_API APlayerCharacter final : public ACharacter
{
	GENERATED_BODY()

private:
	UCameraComponent *TPCameraComp;
	USpotLightComponent *FlashLightComp;
	USpringArmComponent *SpringArmComp;
	UMaterialInstanceDynamic *CameraBloodPPM;
	UAudioComponent *PantAudioComp;
	
	UPROPERTY(EditAnywhere)
	AActor *DeathCameraActor;
	
	UAnimMontage *FireAnim;
	UAnimMontage *DeathAnim;

	bool bWeaponLoaded;
	float NightVisionBlendWeight;
	
	FHitResult LineTraceHitRes;
	FTransform TPCamTransform;
	FVector TraceStart, TraceEnd;
	IInteractable *InteractableItem;

	void Fire();
	FORCEINLINE void MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); }
	FORCEINLINE void MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); }
	FORCEINLINE void Pause() { OnGamePlayStateChange.Broadcast(EGamePlayState::Paused); }
	FORCEINLINE void Interact() { if (InteractableItem) InteractableItem->Interact(this); }
	FORCEINLINE void ToggleNightVision() {
		NightVisionBlendWeight = (NightVisionBlendWeight == 1.0f ? 0.0f : 1.0f);
		TPCameraComp->PostProcessSettings.WeightedBlendables.Array[0].Weight = NightVisionBlendWeight;
	}
	void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

	UFUNCTION()
	void OnDeathAnimEnded(UAnimMontage *Montage, bool bInterrupted);
	
	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnCharacterTakeDamage(AActor *DamagedActor, float Damage,
		const UDamageType *DamageType, AController *InstigatedBy, AActor *DamageCauser);

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
	
	UPROPERTY(BlueprintReadOnly)
	AGrenadeLauncher *GrenadeLauncher;
};
