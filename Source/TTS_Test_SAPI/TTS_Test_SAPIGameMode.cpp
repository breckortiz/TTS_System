// Copyright Epic Games, Inc. All Rights Reserved.

#include "TTS_Test_SAPIGameMode.h"
#include "TTS_Test_SAPICharacter.h"
#include "UObject/ConstructorHelpers.h"

ATTS_Test_SAPIGameMode::ATTS_Test_SAPIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
