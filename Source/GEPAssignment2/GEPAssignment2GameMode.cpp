// Copyright Epic Games, Inc. All Rights Reserved.

#include "GEPAssignment2GameMode.h"
#include "GEPAssignment2Character.h"
#include "UObject/ConstructorHelpers.h"

AGEPAssignment2GameMode::AGEPAssignment2GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
