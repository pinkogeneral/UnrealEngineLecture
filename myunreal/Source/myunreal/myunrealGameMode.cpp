// Copyright Epic Games, Inc. All Rights Reserved.

#include "myunrealGameMode.h"
#include "myunrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

AmyunrealGameMode::AmyunrealGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
