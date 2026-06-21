#include "SpawnPoint.h"
#include "Components/BillboardComponent.h"

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Icon = CreateDefaultSubobject<UBillboardComponent>(TEXT("Icon"));
	RootComponent = Icon;
}