#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellComponent.generated.h"

class ASpellBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THELASTOFFERING_API USpellComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USpellComponent();

	UFUNCTION(BlueprintCallable, Category = "Spells")
	void CastActiveSpell(const FVector& Direction, const FTransform& SpawnTransform);

	UFUNCTION(BlueprintCallable, Category = "Spells")
	void NextSpell();

	UFUNCTION(BlueprintCallable, Category = "Spells")
	void PreviousSpell();

	UFUNCTION(BlueprintPure, Category = "Spells")
	int32 GetActiveSpellIndex() const { return ActiveSpellIndex; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spells")
	TArray<TSubclassOf<ASpellBase>> AvailableSpells;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spells")
	int32 ActiveSpellIndex = 0;

private:
	bool bCanCast = true;
	FTimerHandle CooldownTimer;

	void ResetCooldown();
};