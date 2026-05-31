#include "Spells/SpellBase.h"

ASpellBase::ASpellBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpellBase::Launch(const FVector& Direction)
{
	// Subclases implementan la lógica específica
}