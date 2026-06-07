#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemyBase.h"
#include "EnemyRanged.generated.h"

class ASpellBase;

UCLASS()
class THELASTOFFERING_API AEnemyRanged : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemyRanged();
	virtual void Attack() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<ASpellBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float ProjectileDamage = 10.f;
};