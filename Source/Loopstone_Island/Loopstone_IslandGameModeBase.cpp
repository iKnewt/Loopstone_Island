// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "Loopstone_IslandGameModeBase.h"
#include "ConstructorHelpers.h"
#include "DialogueWidget.h"
#include "DialogueEdge.h"
#include "Dialogue.h"

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

void ALoopstone_IslandGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bEventHasBeenTriggered contains:  %i"), bEventHasBeenTriggered.Num());

	if (BP_DialogueWidget)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld()->GetFirstPlayerController(), BP_DialogueWidget);
	}
	if (!DialogueWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE WIDGET NOT CREATED"));
	}
}

bool ALoopstone_IslandGameModeBase::TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction)
{
	// bEventHasBeenTriggered[static_cast<int>(EventType)] = NewBoolValue;
	//
	// UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(EventType),
	//        (NewBoolValue ? TEXT("true") : TEXT("false")));
	//
	// if (RunFunction)
	// {
	// 	switch (EventType)
	// 	{
	// 	case EEventType::HasRope:
	// 		break;
	// 	default:
	// 		break;
	// 	}
	// }
	return true;
}

void ALoopstone_IslandGameModeBase::StartDialogue(ABaseIslanderCharacter* Islander)
{
	if (Islander->Dialogue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue started with %s"), *Islander->Name);

		CurrentIslander = Islander;
		CurrentDialogueGraph = Islander->Dialogue;
		//
		// if (!DialogueWidget)
		// {
		// 	if (BP_DialogueWidget)
		// 	{
		// 		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld()->GetFirstPlayerController(),
		// 		                                               BP_DialogueWidget);
		// 	}
		// }
		//
		// if (DialogueWidget)
		// {
		// 	DialogueWidget->AddToViewport();
		// 	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		// 	DisableInput(GetWorld()->GetFirstPlayerController());
		// 	CurrentDialogueGraph->CurrentDialogueNode = nullptr;
		// 	// UpdateDialogueBasedOnResponse(0);
		// }
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no dialogue"), *Islander->Name);
	}


	// if (!DialogueWidget)
	// {
	// 	if (BP_DialogueWidget)
	// 	{
	// 		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld()->GetFirstPlayerController(), BP_DialogueWidget);
	// 	}
	// }
	//
	// if (DialogueWidget)
	// {
	// 	DialogueWidget->AddToViewport();
	// 	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	// 	DisableInput(GetWorld()->GetFirstPlayerController());
	// 	CurrentDialogueGraph->CurrentDialogueNode = nullptr;
	// 	// UpdateDialogueBasedOnResponse(0);
	// }
}

void ALoopstone_IslandGameModeBase::CloseDialogue()
{
	// if (DialogueWidget)
	// {
	// 	// TArray<FString> temp;
	// 	// temp.Add("");
	// 	CurrentDialogueGraph->CurrentDialogueNode = nullptr;
	// 	// DialogueWidget->SetDialogueWithOptions(0.05f, "", temp);
	// 	// DialogueWidget->RemoveFromViewport();
	// 	DialogueWidget->RemoveFromParent();
	// 	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	// 	EnableInput(GetWorld()->GetFirstPlayerController());
	// }
}

bool ALoopstone_IslandGameModeBase::UpdateDialogueBasedOnResponse(int ResponseID)
{
	// if (!CurrentDialogueGraph->UpdateCurrentNode(ResponseID))
	// {
	// 	return false;
	// }
	// CurrentDialogueGraph->UpdateEventLibaryBasedOnCurrentNode();
	//
	//
	// FString DialogueText = "";
	// //CurrentDialogueGraph->CurrentDialogueNode->DialogueText.ToString();
	//
	// // Do the check about CONDITION
	//
	// if (DialogueText == "EXIT")
	// {
	// 	CloseDialogue();
	// 	return false;
	// }
	// else if (DialogueText == "CONDITION")
	// {
	// 	for (int i = 0; i < CurrentDialogueGraph->CurrentAvailableOptions.Num(); i++)
	// 	{
	// 		if (UpdateDialogueBasedOnResponse(i))
	// 		{
	// 			break;
	// 		}
	// 	}
	// }
	// else
	// {
	// 	TArray<FString> Options;
	// 	for (auto Option : CurrentDialogueGraph->CurrentAvailableOptions)
	// 	{
	// 		Options.Add(Option->OptionText);
	// 	}
	//
	// 	DialogueWidget->SetDialogueWithOptions(0.03f, DialogueText, Options);
	// }

	return true;
}
