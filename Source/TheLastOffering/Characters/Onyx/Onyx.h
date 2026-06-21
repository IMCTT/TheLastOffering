#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Onyx.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStatsComponent;
class USpellComponent;
class UTLOHUDWidget;



UCLASS()
class THELASTOFFERING_API AOnyx : public ACharacter
{
	GENERATED_BODY()

public:
	AOnyx();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void CastSpell();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStatsComponent> StatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpellComponent> SpellComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SpellSpawnPoint;

	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTLOHUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTLOHUDWidget> HUDWidget;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	float MoveSpeed = 600.f;

private:
	void RotateTowardsMouse();
	
	UFUNCTION()
	void CreateHUD();

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void OnHealthChanged(float CurrentHealth, float MaxHealth);
};