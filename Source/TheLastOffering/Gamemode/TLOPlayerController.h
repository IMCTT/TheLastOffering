#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TLOPlayerController.generated.h"

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

private:
	void HandleMoveForward(const struct FInputActionValue& Value);
	void HandleMoveRight(const struct FInputActionValue& Value);
	void HandleCastSpell();
	void HandleNextSpell();
	void HandlePreviousSpell();

	TObjectPtr<AOnyx> OnyxPawn;
};