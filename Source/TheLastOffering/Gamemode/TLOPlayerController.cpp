#include "TLOPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Spells/SpellComponent.h"
#include "../Characters/Onyx/Onyx.h"

ATLOPlayerController::ATLOPlayerController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATLOPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        if (IMC_Onyx)
            Subsystem->AddMappingContext(IMC_Onyx, 0);
        else
            UE_LOG(LogTemp, Error, TEXT("ATLOPlayerController: IMC_Onyx no asignado"));
    }

    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
    InputMode.SetHideCursorDuringCapture(false);
    SetInputMode(InputMode);
}

void ATLOPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    OnyxPawn = Cast<AOnyx>(InPawn);

    if (!OnyxPawn)
        UE_LOG(LogTemp, Error, TEXT("ATLOPlayerController: el Pawn poseído no es AOnyx"));
}

void ATLOPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
    if (!EIC) return;

    if (IA_MoveForward)
        EIC->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &ATLOPlayerController::HandleMoveForward);

    if (IA_MoveRight)
        EIC->BindAction(IA_MoveRight, ETriggerEvent::Triggered, this, &ATLOPlayerController::HandleMoveRight);

    if (IA_CastSpell)
        EIC->BindAction(IA_CastSpell, ETriggerEvent::Started, this, &ATLOPlayerController::HandleCastSpell);

    if (IA_NextSpell)
        EIC->BindAction(IA_NextSpell, ETriggerEvent::Started, this, &ATLOPlayerController::HandleNextSpell);

    if (IA_PreviousSpell)
        EIC->BindAction(IA_PreviousSpell, ETriggerEvent::Started, this, &ATLOPlayerController::HandlePreviousSpell);
}

void ATLOPlayerController::HandleMoveForward(const FInputActionValue& Value)
{
    if (!OnyxPawn) return;
    OnyxPawn->MoveForward(Value.Get<float>());
}

void ATLOPlayerController::HandleMoveRight(const FInputActionValue& Value)
{
    if (!OnyxPawn) return;
    OnyxPawn->MoveRight(Value.Get<float>());
}

void ATLOPlayerController::HandleCastSpell()
{
    if (!OnyxPawn) return;
    OnyxPawn->CastSpell();
}

void ATLOPlayerController::HandleNextSpell()
{
    if (!OnyxPawn || !OnyxPawn->SpellComponent) return;
    OnyxPawn->SpellComponent->NextSpell();
}

void ATLOPlayerController::HandlePreviousSpell()
{
    if (!OnyxPawn || !OnyxPawn->SpellComponent) return;
    OnyxPawn->SpellComponent->PreviousSpell();
}