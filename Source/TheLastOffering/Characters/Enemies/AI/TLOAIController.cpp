#include "TLOAIController.h"
#include "Characters/Enemies/EnemyBase.h"
#include "Kismet/GameplayStatics.h"

ATLOAIController::ATLOAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATLOAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledEnemy = Cast<AEnemyBase>(InPawn);

	// Intentamos cachear el player con un pequeño delay
	GetWorld()->GetTimerManager().SetTimer(
		FindPlayerTimer,
		this,
		&ATLOAIController::FindPlayer,
		0.5f,
		false
	);

	UE_LOG(LogTemp, Warning, TEXT("AIController: OnPossess ejecutado. Enemy valido: %s"),
		ControlledEnemy ? TEXT("SI") : TEXT("NO"));
}

void ATLOAIController::FindPlayer()
{
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	UE_LOG(LogTemp, Warning, TEXT("AIController: FindPlayer. Player valido: %s"),
		PlayerPawn ? TEXT("SI") : TEXT("NO"));
}

void ATLOAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateChase(DeltaTime);
}

void ATLOAIController::UpdateChase(float DeltaTime)
{
	if (!ControlledEnemy || !PlayerPawn) return;

	TimeSinceLastUpdate += DeltaTime;
	if (TimeSinceLastUpdate < UpdateRate) return;
	TimeSinceLastUpdate = 0.f;

	float Distance = FVector::Dist(
		ControlledEnemy->GetActorLocation(),
		PlayerPawn->GetActorLocation()
	);

	UE_LOG(LogTemp, Warning, TEXT("AIController: Distancia: %.1f | DetectionRange: %.1f"),
		Distance, ControlledEnemy->DetectionRange);

	if (Distance > ControlledEnemy->DetectionRange) return;

	ControlledEnemy->OnTargetDetected(PlayerPawn);

	if (Distance <= ControlledEnemy->AttackRange)
	{
		StopMovement();
		ControlledEnemy->Attack();
		return;
	}

	MoveToActor(PlayerPawn, ControlledEnemy->AttackRange * 0.9f);
}