#include "SpartaGameMode.h"
#include "PlayerPawn.h"
#include "MyPlayerController.h"

ASpartaGameMode::ASpartaGameMode() {
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}