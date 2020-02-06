// Fill out your copyright notice in the Description page of Project Settings.


#include "Loopstone_IslandGameState.h"
#include "DialogueWidget.h"
#include "Dialogue.h"
#include "DialogueEdge.h"
#include "DialogueNode.h"

void ALoopstone_IslandGameState::BeginPlay()
{
	Super::BeginPlay();


	// TEST = 2;

	bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bEventHasBeenTriggered contains:  %i"), bEventHasBeenTriggered.Num());

	if (BP_DialogueWidget)
	{
		// DialogueWidget = CreateWidget(GetWorld()->GetFirstPlayerController(), BP_DialogueWidget);

		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld()->GetFirstPlayerController(), BP_DialogueWidget);
	}
	if (!DialogueWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE WIDGET NOT CREATED"));
	}
}

bool ALoopstone_IslandGameState::TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction)
{
	bEventHasBeenTriggered[static_cast<int>(EventType)] = NewBoolValue;

	UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(EventType),
	       (NewBoolValue ? TEXT("true") : TEXT("false")));
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

void ALoopstone_IslandGameState::StartDialogue(ABaseIslanderCharacter* Islander)
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
		DialogueWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		DisableInput(GetWorld()->GetFirstPlayerController());
		CurrentDialogueGraph->CurrentDialogueNode = nullptr;
		UpdateDialogueBasedOnResponse(0);
		// }
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no dialogue"), *Islander->Name);
	}
}

void ALoopstone_IslandGameState::CloseDialogue()
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

bool ALoopstone_IslandGameState::UpdateDialogueBasedOnResponse(int ResponseID)
{
	if (!CurrentDialogueGraph->UpdateCurrentNode(ResponseID, this))
	{
		return false;
	}
	// // CurrentDialogueGraph->UpdateEventLibaryBasedOnCurrentNode();
	//
	//
	FString DialogueText = "Oh hello....";
	DialogueText = CurrentDialogueGraph->CurrentDialogueNode->DialogueText.ToString();

	// DialogueText = dynamic_cast<UDialogueNode*>(CurrentDialogueGraph->AllNodes[0])->DialogueText.ToString();

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
		TArray<FString> Options;
		for (auto Option : CurrentDialogueGraph->CurrentAvailableOptions)
		{
			Options.Add(Option->OptionText);
		}
			//
			// TArray<FString> Options;
			// Options.Add("one");
			// Options.Add("two");
	
		DialogueWidget->SetDialogueWithOptions(0.03f, DialogueText, Options);
	// }

	return true;
}
