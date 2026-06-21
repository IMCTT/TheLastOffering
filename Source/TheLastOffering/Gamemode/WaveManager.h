#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class ASpawnPoint;
class AEnemyBase;
class UTLOHUDWidget;

// Define qué enemigo y cuántos spawnea por oleada
USTRUCT(BlueprintType)
struct FWaveEnemyEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AEnemyBase> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseCount = 3;
};

UCLASS()
class THELASTOFFERING_API AWaveManager : public AActor
{
    GENERATED_BODY()

public:
    AWaveManager();

    // Inicia el sistema de oleadas (llamado por el GameMode)
    UFUNCTION(BlueprintCallable, Category = "Waves")
    void StartWaves();

protected:
    virtual void BeginPlay() override;

    // Spawn points colocados en el nivel
    UPROPERTY(EditAnywhere, Category = "Waves")
    TArray<TSubclassOf<ASpawnPoint>> SpawnPointFilter; // sin uso directo, placeholder si se desea filtrar

    // Tipos de enemigos disponibles para las oleadas
    UPROPERTY(EditAnywhere, Category = "Waves")
    TArray<FWaveEnemyEntry> WaveEnemies;

    // Tiempo de espera entre oleadas
    UPROPERTY(EditAnywhere, Category = "Waves")
    float TimeBetweenWaves = 5.f;

    // Cuánto escala el HP de los enemigos por oleada (multiplicador acumulativo)
    UPROPERTY(EditAnywhere, Category = "Waves")
    float HealthScalePerWave = 0.15f;

    // Cuánto escala el daño de los enemigos por oleada
    UPROPERTY(EditAnywhere, Category = "Waves")
    float DamageScalePerWave = 0.10f;

    // Enemigos extra fijos que se suman cada oleada (además del BaseCount)
    UPROPERTY(EditAnywhere, Category = "Waves")
    int32 ExtraEnemiesPerWave = 2;

private:
    int32 CurrentWave = 0;
    int32 EnemiesAlive = 0;

    TArray<TObjectPtr<ASpawnPoint>> CachedSpawnPoints;
    TObjectPtr<UTLOHUDWidget> HUDWidget;

    FTimerHandle NextWaveTimer;

    void CacheSpawnPoints();
    void BeginNextWave();
    void SpawnWaveEnemies();
    void SpawnSingleEnemy(TSubclassOf<AEnemyBase> EnemyClass, int32 WaveNumber);

    UFUNCTION()
    void OnEnemyDeath();

    void UpdateHUD();
};