#include "Spells/SpellComponent.h"
#include "Spells/SpellBase.h"
#include "Engine/World.h"

USpellComponent::USpellComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USpellComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USpellComponent::CastActiveSpell(const FVector& Direction, const FTransform& SpawnTransform)
{
	if (!bCanCast || AvailableSpells.IsEmpty()) return;

	TSubclassOf<ASpellBase> SpellClass = AvailableSpells[ActiveSpellIndex];
	if (!SpellClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());

	FTransform AdjustedTransform = SpawnTransform;
	AdjustedTransform.SetRotation(Direction.Rotation().Quaternion());

	ASpellBase* Spell = GetWorld()->SpawnActor<ASpellBase>(
		SpellClass,
		AdjustedTransform,
		SpawnParams
	);

	if (Spell)
	{
		Spell->Launch(Direction);

		bCanCast = false;
		GetWorld()->GetTimerManager().SetTimer(
			CooldownTimer,
			this,
			&USpellComponent::ResetCooldown,
			Spell->Cooldown,
			false
		);
	}
}

void USpellComponent::NextSpell()
{
	if (AvailableSpells.IsEmpty()) return;
	ActiveSpellIndex = (ActiveSpellIndex + 1) % AvailableSpells.Num();
}

void USpellComponent::PreviousSpell()
{
	if (AvailableSpells.IsEmpty()) return;
	ActiveSpellIndex = (ActiveSpellIndex - 1 + AvailableSpells.Num()) % AvailableSpells.Num();
}

void USpellComponent::ResetCooldown()
{
	bCanCast = true;
}