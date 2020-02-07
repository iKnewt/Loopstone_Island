// Fill out your copyright notice in the Description page of Project Settings.


#include "Loopstone_IslandGameState.h"
#include "DialogueWidget.h"
#include "Dialogue.h"
#include "DialogueEdge.h"
#include "DialogueNode.h"

void ALoopstone_IslandGameState::BeginPlay()
{
	Super::BeginPlay();

	bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bEventHasBeenTriggered contains:  %i"), bEventHasBeenTriggered.Num());

	bTopicHasBeenRevealed.SetNum(static_cast<int>(ETopic::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bTopicHasBeenRevealed contains:  %i"), bTopicHasBeenRevealed.Num());
	
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
	if(!Islander || !DialogueWidget)
	{
		return;
	}

	if (Islander->Dialogue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue started with %s"), *Islander->Name);

		CurrentIslander = Islander;
		CurrentDialogue = Islander->Dialogue;

		DialogueWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		DisableInput(GetWorld()->GetFirstPlayerController());
		CurrentDialogue->CurrentDialogueNode = nullptr;
		UpdateDialogueBasedOnResponse(0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no dialogue"), *Islander->Name);
	}
}

void ALoopstone_IslandGameState::CloseDialogue()
{
	if (DialogueWidget)
	{
		TArray<FString> temp;
		// temp.Add(" ");
		CurrentDialogue->CurrentDialogueNode = nullptr;
		DialogueWidget->SetDialogueWithOptions(0.05f, " ", temp);
		// DialogueWidget->RemoveFromViewport();
			// DialogueWidget->SetDialogueWithOptions(0.01f, DialogueText, Options);
		DialogueWidget->RemoveFromParent();
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

bool ALoopstone_IslandGameState::UpdateDialogueBasedOnResponse(int ResponseID)
{
	if (!CurrentDialogue->UpdateCurrentNode(ResponseID, this))
	{
		CloseDialogue();
		return false;
	}

	CurrentDialogue->UpdateEventLibaryBasedOnCurrentNode(this);

	FString DialogueText = "Oh hello....";

	// update the dialogue widget
	DialogueText = CurrentDialogue->CurrentDialogueNode->DialogueText.ToString();

	TArray<FString> Options;
	for (auto Option : CurrentDialogue->CurrentAvailableOptions)
	{
		Options.Add(Option->OptionText);
	}

	DialogueWidget->SetDialogueWithOptions(0.01f, DialogueText, Options);

	return true;
}
