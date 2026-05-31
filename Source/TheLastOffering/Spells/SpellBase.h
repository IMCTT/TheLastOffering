#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellBase.generated.h"

UCLASS(Abstract)
class THELASTOFFERING_API ASpellBase : public AActor
{
	GENERATED_BODY()

public:
	ASpellBase();

	virtual void Launch(const FVector& Direction);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell|Stats")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell|Stats")
	float Cooldown = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell|Info")
	FName SpellName = "Base Spell";
};