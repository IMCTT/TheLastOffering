#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemyBase.h"
#include "EnemyMelee.generated.h"

UCLASS()
class THELASTOFFERING_API AEnemyMelee : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemyMelee();
	virtual void Attack() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float MeleeDamage = 15.f;
};