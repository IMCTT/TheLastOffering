#include "StatsComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Spells/SpellComponent.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UStatsComponent::ApplyDamage(float Damage, AActor* Instigator)
{
	if (IsDead() || Damage <= 0.f) return;

	CurrentHealth = FMath::Max(CurrentHealth - Damage, 0.f);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

	if (DamageSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DamageSound, GetOwner()->GetActorLocation());

	UE_LOG(LogTemp, Warning, TEXT("[StatsComponent] %s recibió %.1f de daño. HP: %.1f/%.1f"),
		*GetOwner()->GetName(), Damage, CurrentHealth, MaxHealth);

	if (IsDead())
	{
		if (DeathSound)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetOwner()->GetActorLocation());

		OnDeath.Broadcast();
	}
}

void UStatsComponent::Heal(float Amount)
{
	if (IsDead() || Amount <= 0.f) return;
	CurrentHealth = FMath::Min(CurrentHealth + Amount, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

bool UStatsComponent::IsDead() const
{
	return CurrentHealth <= 0.f;
}