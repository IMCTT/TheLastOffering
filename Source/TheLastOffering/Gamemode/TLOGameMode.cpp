#include "TLOGameMode.h"
#include "TLOPlayerController.h"
#include "../Characters/Onyx/Onyx.h"

ATLOGameMode::ATLOGameMode()
{
	PlayerControllerClass = ATLOPlayerController::StaticClass();
	DefaultPawnClass      = AOnyx::StaticClass();
}