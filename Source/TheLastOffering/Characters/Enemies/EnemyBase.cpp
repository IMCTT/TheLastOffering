#include "Characters/Enemies/EnemyBase.h"
#include "Components/StatsComponent.h"
#include "AI/TLOAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	
	//Le dice a unreal que el controller posee a este enemigo
	AIControllerClass = ATLOAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	StatsComponent->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
	
	SpawnDefaultController();
}

void AEnemyBase::OnTargetDetected(AActor* Target)
{
	CurrentTarget = Target;
}

void AEnemyBase::Attack()
{

}

void AEnemyBase::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	UE_LOG(LogTemp, Warning, TEXT("[EnemyBase] %s murio"), *GetName());
}

void AEnemyBase::ResetAttackCooldown()
{
	bCanAttack = true;
}