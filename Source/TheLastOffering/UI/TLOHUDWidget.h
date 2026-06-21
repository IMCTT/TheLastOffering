#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TLOHUDWidget.generated.h"


UCLASS()
class THELASTOFFERING_API UTLOHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// barra de vida, esto lo llama onyx nada mas
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	// waves , esto lo va a ver el wave manager
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateWave(int32 WaveNumber);

	// enemigos
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateEnemiesRemaining(int32 EnemiesRemaining);

	// spells
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateActiveSpell(FName SpellName);

protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> WaveText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> EnemiesText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SpellText;
};