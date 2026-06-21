#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/TLOHUDWidget.h"
#include "TLOPlayerController.generated.h"  

void UpdateHUDHealth(float CurrentHealth, float MaxHealth);

class UInputMappingContext;
class UInputAction;
class AOnyx;

UCLASS()
class THELASTOFFERING_API ATLOPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATLOPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Onyx;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_MoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_MoveRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_CastSpell;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_NextSpell;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_PreviousSpell;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTLOHUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UTLOHUDWidget> HUDWidget;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHUDHealth(float CurrentHealth, float MaxHealth);
	
private:
	void HandleMoveForward(const struct FInputActionValue& Value);
	void HandleMoveRight(const struct FInputActionValue& Value);
	void HandleCastSpell();
	void HandleNextSpell();
	void HandlePreviousSpell();

	TObjectPtr<AOnyx> OnyxPawn;
};