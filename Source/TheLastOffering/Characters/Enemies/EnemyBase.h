#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UStatsComponent;

UCLASS(Abstract)
class THELASTOFFERING_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();

	virtual void OnTargetDetected(AActor* Target);
	virtual void Attack();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStatsComponent> StatsComponent;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TObjectPtr<AActor> CurrentTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float DetectionRange = 800.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float AttackRange = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	float AttackCooldown = 1.f;

	bool bCanAttack = true;
	FTimerHandle AttackCooldownTimer;

	void ResetAttackCooldown();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();
};