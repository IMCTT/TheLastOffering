#include "EnemyRanged.h"
#include "Spells/SpellBase.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyRanged::AEnemyRanged()
{
	AttackRange = 600.f;
	AttackCooldown = 2.f;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
}

void AEnemyRanged::Attack()
{
	if (!bCanAttack || !CurrentTarget || !ProjectileClass) return;

	float Distance = FVector::Dist(GetActorLocation(), CurrentTarget->GetActorLocation());
	if (Distance > AttackRange) return;

	FVector Direction = (CurrentTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	Direction.Z = 0.f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;

	ASpellBase* Projectile = GetWorld()->SpawnActor<ASpellBase>(
		ProjectileClass,
		GetActorLocation(),
		Direction.Rotation(),
		SpawnParams
	);

	if (Projectile)
	{
		Projectile->Damage = ProjectileDamage;
		Projectile->Launch(Direction);
	}

	bCanAttack = false;
	GetWorld()->GetTimerManager().SetTimer(
		AttackCooldownTimer,
		this,
		&AEnemyBase::ResetAttackCooldown,
		AttackCooldown,
		false
	);
}