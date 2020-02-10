// Fill out your copyright notice in the Description page of Project Settings.


#include "Loopstone_IslandGameState.h"
#include "DialogueWidget.h"
#include "Dialogue.h"
#include "DialogueEdge.h"
#include "DialogueNode.h"
#include "SunSky.h"
#include "InteractableObjectBase.h"
#include "InventoryWidget.h"

void ALoopstone_IslandGameState::BeginPlay()
{
	Super::BeginPlay();

	bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bEventHasBeenTriggered contains:  %i"), bEventHasBeenTriggered.Num());

	bTopicHasBeenRevealed.SetNum(static_cast<int>(ETopic::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bTopicHasBeenRevealed contains:  %i"), bTopicHasBeenRevealed.Num());

	
	if (BP_DialogueWidget)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld()->GetFirstPlayerController(), BP_DialogueWidget);
		DialogueWidget->AddToViewport();
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (!DialogueWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE WIDGET NOT CREATED"));
	}

	if (BP_InventoryWidget)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld()->GetFirstPlayerController(), BP_InventoryWidget);
		InventoryWidget->AddToViewport();
	}
	if (!InventoryWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("INVENTORY WIDGET NOT CREATED"));
	}

	
}

bool ALoopstone_IslandGameState::TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction)
{
	bEventHasBeenTriggered[static_cast<int>(EventType)] = NewBoolValue;

	UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(EventType),
	       (NewBoolValue ? TEXT("true") : TEXT("false")));

	if(!InventoryWidget)
	{
		return true;
	}
	
	if (RunFunction)
	{
		switch (EventType)
		{
		case EEventType::HasTape:
		{
			InventoryWidget->EditInventoryItem(EItem::Tape, NewBoolValue);
			break;
		}
		case EEventType::HasRope:
		{
			InventoryWidget->EditInventoryItem(EItem::Rope, NewBoolValue);
			break;
		}
		case EEventType::HasKnife:
		{
			InventoryWidget->EditInventoryItem(EItem::Knife, NewBoolValue);
			break;
		}
		case EEventType::None:
			break;
		default:;
		}
	}

	return true;
}

bool ALoopstone_IslandGameState::InteractWithObject(AInteractableObjectBase* InteractableObject)
{
	// CHECK CONDITIONS

	// todo make better implementation of condition checking
	for (auto Element : InteractableObject->EventBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != this->bEventHasBeenTriggered[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}
	for (auto Element : InteractableObject->TopicBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != this->bTopicHasBeenRevealed[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}

	if (InteractableObject->TimeOfDayCondition != ETimeOfDay::None &&
		InteractableObject->TimeOfDayCondition != this->CurrentTimeOfDay)
	{
		return false;
	}
	if (InteractableObject->ActiveStoryCondition != EStory::None &&
		InteractableObject->ActiveStoryCondition != this->CurrentStory)
	{
		return false;
	}


	// if all conditions pass

	// do any local changes to the object
	InteractableObject->Interact();

	// CHECK GLOBAL EVENT TRIGGER
	// todo make better implementation for event trigger
	for (auto Element : InteractableObject->EventBoolsToChange)
	{
		this->TriggerEvent(Element.Key, Element.Value);
	}
	for (auto Element2 : InteractableObject->TopicBoolsToChange)
	{
		this->bTopicHasBeenRevealed[static_cast<int>(Element2.Key)] = Element2.Value;
		// GameState->bEventHasBeenTriggered[static_cast<int>(Element.Key)] = Element.Value;
	}

	if (InteractableObject->TimeOfDayChange != ETimeOfDay::None)
	{
		this->ChangeTimeOfDay(InteractableObject->TimeOfDayChange);
		// do other stuff to change day??
	}
	if (InteractableObject->ActiveStoryChange != EStory::None)
	{
		this->ChangeStory(InteractableObject->ActiveStoryChange);
		// do other stuff to change story??
	}
	return true;
}

bool ALoopstone_IslandGameState::StartDialogue(ABaseIslanderCharacter* Islander)
{
	if (!Islander || !DialogueWidget)
	{
		return false;
	}

	if (Islander->Dialogue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue started with %s"), *Islander->Name);

		CurrentIslander = Islander;
		CurrentDialogue = Islander->Dialogue;

		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
		// DialogueWidget->SetUserFocus(GetWorld()->GetFirstPlayerController());
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		CurrentDialogue->CurrentDialogueNode = nullptr;

		DialogueWidget->SetSpeakerName(Islander->Name);
		UpdateDialogueBasedOnResponse(0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no dialogue"), *Islander->Name);
	}
	return true;
}

void ALoopstone_IslandGameState::CloseDialogue()
{
	if (DialogueWidget)
	{
		CurrentIslander = nullptr;
		CurrentDialogue->CurrentDialogueNode = nullptr;
		CurrentDialogue = nullptr;

		TArray<FString> temp;
		DialogueWidget->SetDialogueWithOptions(0.05f, " ", temp);

		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	}
}

bool ALoopstone_IslandGameState::UpdateDialogueBasedOnResponse(int ResponseID)
{
	if (!CurrentDialogue->UpdateCurrentNode(ResponseID, this))
	{
		CloseDialogue();
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("trying to update event library"));
	CurrentDialogue->UpdateEventLibaryBasedOnCurrentNode(this);

	FString DialogueText = "Oh hello....";

	// update the dialogue widget
	DialogueText = CurrentDialogue->CurrentDialogueNode->DialogueText.ToString();

	// todo find better solution to catch this
	if (DialogueText == "CONDITION")
	{
		CloseDialogue();
		return false;
	}

	TArray<FString> Options;
	for (auto Option : CurrentDialogue->CurrentAvailableOptions)
	{
		Options.Add(Option->OptionText);
	}

	DialogueWidget->SetDialogueWithOptions(0.01f, DialogueText, Options);

	return true;
}

void ALoopstone_IslandGameState::ChangeTimeOfDay(ETimeOfDay NewTimeOfDay)
{
	CurrentTimeOfDay = NewTimeOfDay;
	if (SunSky)
	{
		SunSky->ChangeTimeOfDay(NewTimeOfDay);
	}
}

void ALoopstone_IslandGameState::ChangeStory(EStory NewStory)
{
	CurrentStory = NewStory;

	// Do functionality if any.
}
