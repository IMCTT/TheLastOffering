#include "Spells/FireSpell.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StatsComponent.h"

AFireSpell::AFireSpell()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetSphereRadius(16.f);
	CollisionSphere->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = CollisionSphere;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AFireSpell::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentHit.AddDynamic(this, &AFireSpell::OnHit);
	SetLifeSpan(LifeSpan);
}

void AFireSpell::Launch(const FVector& Direction)
{
	if (ProjectileMovement)
		ProjectileMovement->Velocity = Direction.GetSafeNormal() * ProjectileSpeed;
}

void AFireSpell::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor || OtherActor == GetOwner()) return;

	UStatsComponent* StatsComp = OtherActor->FindComponentByClass<UStatsComponent>();
	if (StatsComp)
		StatsComp->ApplyDamage(Damage, GetOwner());

	Destroy();
}