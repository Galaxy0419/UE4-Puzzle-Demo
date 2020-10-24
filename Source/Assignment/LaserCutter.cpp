#include "LaserCutter.h"

#include "Kismet/KismetMathLibrary.h"

#include "PlayerCharacter.h"

ALaserCutter::ALaserCutter()
	: TimeElapsed(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	/* Laser Mesh */
	LaserMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser Root Mesh Component"));
	RootComponent = LaserMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LaserMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	LaserMeshComp->SetStaticMesh(LaserMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> LaserMaterialAsset(TEXT("Material'/Game/Materials/M_Laser.M_Laser'"));
	LaserMeshComp->SetMaterial(0, LaserMaterialAsset.Object);

	LaserMeshComp->SetRelativeScale3D(FVector(0.125f, 0.125f, 4.0f));
	LaserMeshComp->SetCollisionProfileName("Trigger");
	LaserMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ALaserCutter::OnLaserBeginOverlap);
}

void ALaserCutter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeElapsed += DeltaTime;
	LerpCurrent = UKismetMathLibrary::VInterpTo_Constant(LerpStart, LerpEnd, TimeElapsed, 128.0f);

	if ((LerpEnd - LerpCurrent).IsNearlyZero(0.5f)) {
		SetActorLocation(LerpEnd);
		LerpEnd = LerpStart;
		LerpStart = GetActorLocation();
		TimeElapsed = 0.0f;
	} else {
		SetActorLocation(LerpCurrent);
	}
}

void ALaserCutter::OnLaserBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<APlayerCharacter>(OtherActor))
		OtherActor->TakeDamage(-0.2f, FDamageEvent(), nullptr, this);
}
