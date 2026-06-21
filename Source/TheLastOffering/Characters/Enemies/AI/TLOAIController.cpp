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
	GetWorld()->GetTimerManager().SetTimer(	FindPlayerTimer,this,&ATLOAIController::FindPlayer,0.5f,
		false);
	
}

void ATLOAIController::FindPlayer()
{
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
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
	
	if (TimeSinceLastUpdate < UpdateRate) return; //resetea el tiempo asi no busca constantemente
	
	TimeSinceLastUpdate = 0.f;

	// saca la distancia entre pawn y enemigo
	float Distance = FVector::Dist(ControlledEnemy->GetActorLocation(),PlayerPawn->GetActorLocation());

	

	if (Distance > ControlledEnemy->DetectionRange) return;

	ControlledEnemy->OnTargetDetected(PlayerPawn);

	if (Distance <= ControlledEnemy->AttackRange)
	{
		StopMovement();
		ControlledEnemy->Attack();
		return;
	}

	MoveToActor(PlayerPawn, ControlledEnemy->AttackRange * 0.9f); // se frena antes asi no se bugea
}