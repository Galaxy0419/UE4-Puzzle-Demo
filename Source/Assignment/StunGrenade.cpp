#include "StunGrenade.h"

AStunGrenade::AStunGrenade()
{
	PrimaryActorTick.bCanEverTick = false;

	/* Grenade Mesh Component */
	GrenadeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Static Mesh Component"));
	GrenadeMeshComp->SetupAttachment(RootComponent);

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

	/* Projectile Movement Component */
	GrenadeProjMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Grenade Projectile Movement Component"));
	GrenadeProjMoveComp->bShouldBounce = false;
	GrenadeProjMoveComp->OnProjectileStop.AddDynamic(this, &AStunGrenade::OnGrenadeStop);
}

void AStunGrenade::BeginPlay()
{
	Super::BeginPlay();

	GrenadeProjMoveComp->Velocity = ForwardVector * 2048.0f;
}

void AStunGrenade::OnGrenadeStop(const FHitResult& ImpactResult)
{
	Destroy();
}
