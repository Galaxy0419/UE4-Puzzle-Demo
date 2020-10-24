#include "StunGrenade.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AStunGrenade::AStunGrenade()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Grenade Mesh Component */
	GrenadeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Static Mesh Component"));
	RootComponent = GrenadeMeshComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	GrenadeMeshComp->SetStaticMesh(SphereMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial>
		GrenadeMaterialAsset(TEXT("Material'/Game/Materials/M_StunGrenade.M_StunGrenade'"));
	GrenadeMeshComp->SetMaterial(0, GrenadeMaterialAsset.Object);
	
	GrenadeMeshComp->SetRelativeScale3D(FVector(0.125f));
	
	/* Lightning Niagara Particle System */
	LightningNiagComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Lightning Niagara Particle System"));
	LightningNiagComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>
		LightningNiagAsset(TEXT("NiagaraSystem'/Game/Particle_Systems/NS_Lightning.NS_Lightning'"));
	LightningNiagComp->SetAsset(LightningNiagAsset.Object);

	/* Explosion Audio Component */
	ExplosionAudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Explosion Audio Component"));
	ExplosionAudioComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundWave>
		ExplosionSoundAsset(TEXT("SoundWave'/Game/Audios/SW_StunExplosion.SW_StunExplosion'"));
	ExplosionAudioComp->SetSound(ExplosionSoundAsset.Object);

	ExplosionAudioComp->bAutoActivate = false;
	ExplosionAudioComp->OnAudioFinished.AddDynamic(this, &AStunGrenade::OnExplosionSoundFinished);

	/* Projectile Movement Component */
	GrenadeProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Grenade Projectile Movement Component"));
	GrenadeProjMoveComp->bShouldBounce = false;
	GrenadeProjMoveComp->OnProjectileStop.AddDynamic(this, &AStunGrenade::OnGrenadeStop);

	/* Load Explosion Decal Material */
	static ConstructorHelpers::FObjectFinder<UMaterial>
		ExplosionDecalAsset(TEXT("Material'/Game/Materials/M_ExplosionDecal.M_ExplosionDecal'"));
	ExplosionDecal = ExplosionDecalAsset.Object;
}

void AStunGrenade::BeginPlay()
{
	Super::BeginPlay();

	GrenadeProjMoveComp->Velocity = ForwardVector * 2048.0f;
}

void AStunGrenade::OnGrenadeStop(const FHitResult& ImpactResult)
{
	/* Play Particle Effects */
	LightningNiagComp->SetRelativeScale3D(FVector(16.0f));
	LightningNiagComp->Activate(true);

	/* Play Explosion Sound */
	ExplosionAudioComp->Play();

	/* Spawn Decal */
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ExplosionDecal,
        FVector(0.0625f, 64.0f, 64.0f), ImpactResult.ImpactPoint,
        UKismetMathLibrary::MakeRotFromX(ImpactResult.ImpactNormal), 16.0f);
}

void AStunGrenade::OnExplosionSoundFinished()
{
	Destroy();
}
