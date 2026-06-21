#include "WaveManager.h"
#include "SpawnPoint.h"
#include "Characters/Enemies/EnemyBase.h"
#include "Components/StatsComponent.h"
#include "UI/TLOHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/Onyx/Onyx.h"

AWaveManager::AWaveManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AWaveManager::BeginPlay()
{
    Super::BeginPlay();
    CacheSpawnPoints();

    // Tomamos referencia al HUD de Onyx para actualizarlo
    AOnyx* Onyx = Cast<AOnyx>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (Onyx)
        HUDWidget = Onyx->HUDWidget;
}

void AWaveManager::CacheSpawnPoints()
{
    TArray<AActor*> FoundPoints;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), FoundPoints);

    CachedSpawnPoints.Empty();
    for (AActor* Actor : FoundPoints)
    {
        if (ASpawnPoint* SP = Cast<ASpawnPoint>(Actor))
            CachedSpawnPoints.Add(SP);
    }

    UE_LOG(LogTemp, Warning, TEXT("[WaveManager] %d spawn points encontrados"), CachedSpawnPoints.Num());
}

void AWaveManager::StartWaves()
{
    CurrentWave = 0;
    BeginNextWave();
}

void AWaveManager::BeginNextWave()
{
    CurrentWave++;
    UE_LOG(LogTemp, Warning, TEXT("[WaveManager] Comenzando oleada %d"), CurrentWave);

    SpawnWaveEnemies();
    UpdateHUD();
}

void AWaveManager::SpawnWaveEnemies()
{
    UE_LOG(LogTemp, Warning, TEXT("[WaveManager] SpawnPoints: %d | WaveEnemies entries: %d"),
        CachedSpawnPoints.Num(), WaveEnemies.Num());

    if (CachedSpawnPoints.IsEmpty() || WaveEnemies.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("[WaveManager] No hay spawn points o tipos de enemigos configurados"));
        return;
    }

    EnemiesAlive = 0;

    for (const FWaveEnemyEntry& Entry : WaveEnemies)
    {
        UE_LOG(LogTemp, Warning, TEXT("[WaveManager] Entry - EnemyClass valido: %s | BaseCount: %d"),
            Entry.EnemyClass ? TEXT("SI") : TEXT("NO"), Entry.BaseCount);

        if (!Entry.EnemyClass) continue;

        int32 CountThisWave = Entry.BaseCount + (ExtraEnemiesPerWave * (CurrentWave - 1));

        for (int32 i = 0; i < CountThisWave; i++)
        {
            SpawnSingleEnemy(Entry.EnemyClass, CurrentWave);
        }
    }
}

void AWaveManager::SpawnSingleEnemy(TSubclassOf<AEnemyBase> EnemyClass, int32 WaveNumber)
{
    if (CachedSpawnPoints.IsEmpty()) return;

    int32 RandomIndex = FMath::RandRange(0, CachedSpawnPoints.Num() - 1);
    ASpawnPoint* SpawnPoint = CachedSpawnPoints[RandomIndex];
    if (!SpawnPoint) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AEnemyBase* NewEnemy = GetWorld()->SpawnActor<AEnemyBase>(
        EnemyClass,
        SpawnPoint->GetActorLocation(),
        SpawnPoint->GetActorRotation(),
        SpawnParams
    );

    if (NewEnemy)
    {
        EnemiesAlive++;

        // Escalado de dificultad
        float HealthMultiplier = 1.f + (HealthScalePerWave * (WaveNumber - 1));
        float DamageMultiplier = 1.f + (DamageScalePerWave * (WaveNumber - 1));

        if (NewEnemy->StatsComponent)
        {
            NewEnemy->StatsComponent->SetMaxHealthMultiplier(HealthMultiplier);
            NewEnemy->StatsComponent->OnDeath.AddDynamic(this, &AWaveManager::OnEnemyDeath);
        }

        // El daño se escala desde las subclases vía multiplicador genérico
        NewEnemy->DamageMultiplier = DamageMultiplier;
    }
}

void AWaveManager::OnEnemyDeath()
{
    EnemiesAlive = FMath::Max(0, EnemiesAlive - 1);
    UpdateHUD();

    UE_LOG(LogTemp, Warning, TEXT("[WaveManager] Enemigo murió. Quedan: %d"), EnemiesAlive);

    if (EnemiesAlive <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("[WaveManager] Oleada %d completada. Próxima en %.1f s"),
            CurrentWave, TimeBetweenWaves);

        GetWorld()->GetTimerManager().SetTimer(
            NextWaveTimer,
            this,
            &AWaveManager::BeginNextWave,
            TimeBetweenWaves,
            false
        );
    }
}

void AWaveManager::UpdateHUD()
{
    if (HUDWidget)
    {
        HUDWidget->UpdateWave(CurrentWave);
        HUDWidget->UpdateEnemiesRemaining(EnemiesAlive);
    }
}