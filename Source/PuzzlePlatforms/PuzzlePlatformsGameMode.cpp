// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatforms/PuzzlePlatformsGameMode.h"
#include "PuzzlePlatforms/PuzzlePlatformsCharacter.h"
#include <UObject/ConstructorHelpers.h>

APuzzlePlatformsGameMode::APuzzlePlatformsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
