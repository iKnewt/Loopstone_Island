// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "Loopstone_IslandGameModeBase.h"
#include "ConstructorHelpers.h"
#include "GUI/DialogueWidget.h"
#include "Dialogue/DialogueEdge.h"
#include "Dialogue/Dialogue.h"

ALoopstone_IslandGameModeBase::ALoopstone_IslandGameModeBase()
	: Super()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Assets/Characters/Player/BP_PlayerCharacter.uasset"));
	// DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	// HUDClass = AFirstPersonBaseHUD::StaticClass();
	//
	//

	//GameDialogue->PrintAllDialogue();

	// bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);
	// UE_LOG(LogTemp, Warning, TEXT("bEventHasBeenTriggered contains:  %i"), bEventHasBeenTriggered.Num());
	//
	// if (BP_DialogueWidget)
	// {
	// 	DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld()->GetFirstPlayerController(), BP_DialogueWidget);
	// }
	// if(!DialogueWidget)
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("DIALOGUE WIDGET NOT CREATED"));
	// }
}

