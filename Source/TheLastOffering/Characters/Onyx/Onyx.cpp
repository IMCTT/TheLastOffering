#include "Onyx.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Components/StatsComponent.h"
#include "../../Spells/SpellComponent.h"

AOnyx::AOnyx()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 800.f;
    SpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
    SpringArm->bDoCollisionTest = false;
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritRoll = false;
    SpringArm->bInheritYaw = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));

    SpellComponent = CreateDefaultSubobject<USpellComponent>(TEXT("SpellComponent"));

    SpellSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpellSpawnPoint"));
    SpellSpawnPoint->SetupAttachment(RootComponent);
    SpellSpawnPoint->SetRelativeLocation(FVector(50.f, 0.f, 0.f));

    GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    bUseControllerRotationYaw = false;
}

void AOnyx::BeginPlay()
{
    Super::BeginPlay();
    StatsComponent->OnDeath.AddDynamic(this, &AOnyx::OnDeath);
}

void AOnyx::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    RotateTowardsMouse();
}

void AOnyx::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Input manejado por ATLOPlayerController
}

void AOnyx::MoveForward(float Value)
{
    if (Value == 0.f) return;
    const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(Direction, Value);
}

void AOnyx::MoveRight(float Value)
{
    if (Value == 0.f) return;
    const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(Direction, Value);
}

void AOnyx::CastSpell()
{
    if (!SpellComponent || !SpellSpawnPoint) return;
    SpellComponent->CastActiveSpell(
        GetActorForwardVector(),
        SpellSpawnPoint->GetComponentTransform()
    );
}

void AOnyx::RotateTowardsMouse()
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;

    FHitResult HitResult;
    PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    if (HitResult.bBlockingHit)
    {
        FVector Direction = HitResult.Location - GetActorLocation();
        Direction.Z = 0.f;
        if (!Direction.IsNearlyZero())
            SetActorRotation(Direction.Rotation());
    }
}

void AOnyx::OnDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Onyx ha muerto"));
    // Aquí irá la lógica de game over
}