#pragma once

#include "CoreMinimal.h"
#include "Spells/SpellBase.h"
#include "FireSpell.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class THELASTOFFERING_API AFireSpell : public ASpellBase
{
	GENERATED_BODY()

public:
	AFireSpell();

	virtual void Launch(const FVector& Direction) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell|Stats")
	float ProjectileSpeed = 1500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell|Stats")
	float LifeSpan = 3.f;
};