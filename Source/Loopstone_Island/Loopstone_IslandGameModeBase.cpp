// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "Loopstone_IslandGameModeBase.h"
#include "PlayerCharacter.h"
#include "ConstructorHelpers.h"

ALoopstone_IslandGameModeBase::ALoopstone_IslandGameModeBase()
: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Assets/Characters/Player/BP_PlayerCharacter.uasset"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	// HUDClass = AFirstPersonBaseHUD::StaticClass();
}
