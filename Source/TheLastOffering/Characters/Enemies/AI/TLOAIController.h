#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TLOAIController.generated.h"

class AEnemyBase;

UCLASS()
class THELASTOFFERING_API ATLOAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATLOAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

private:
	TObjectPtr<AEnemyBase> ControlledEnemy;
	TObjectPtr<APawn> PlayerPawn;
	FTimerHandle FindPlayerTimer;
	void FindPlayer();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float UpdateRate = 0.2f;

	float TimeSinceLastUpdate = 0.f;

	void UpdateChase(float DeltaTime);
	
	
};