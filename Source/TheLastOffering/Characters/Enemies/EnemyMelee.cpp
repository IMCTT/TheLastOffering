#include "EnemyMelee.h"
#include "Components/StatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyMelee::AEnemyMelee()
{
	AttackRange = 100.f;
	AttackCooldown = 1.2f;
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
}

void AEnemyMelee::Attack()
{
	if (!bCanAttack || !CurrentTarget) return;

	float Distance = FVector::Dist(GetActorLocation(), CurrentTarget->GetActorLocation());
	if (Distance > AttackRange) return;

	UStatsComponent* TargetStats = CurrentTarget->FindComponentByClass<UStatsComponent>();
	if (TargetStats)
		TargetStats->ApplyDamage(MeleeDamage, this);

	bCanAttack = false;
	GetWorld()->GetTimerManager().SetTimer(
		AttackCooldownTimer,
		this,
		&AEnemyBase::ResetAttackCooldown,
		AttackCooldown,
		false
	);
}