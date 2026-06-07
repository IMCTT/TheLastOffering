#include "Characters/Enemies/EnemyBase.h"
#include "Components/StatsComponent.h"
#include "AI/TLOAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

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
	// Subclases implementan el ataque
}

void AEnemyBase::OnDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(2.f);

	UE_LOG(LogTemp, Warning, TEXT("[EnemyBase] %s murio"), *GetName());
}

void AEnemyBase::ResetAttackCooldown()
{
	bCanAttack = true;
}