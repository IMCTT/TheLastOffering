#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class THELASTOFFERING_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	ASpawnPoint();

protected:
	// Visualización en el editor
	UPROPERTY(VisibleAnywhere, Category = "Spawn")
	TObjectPtr<class UBillboardComponent> Icon;
};