// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue.h"
#include "DialogueNode.h"
#include "DialogueEdge.h"
#include "UObject/Class.h"
#include "Loopstone_IslandGameState.h"

#define LOCTEXT_NAMESPACE "Dialogue"

UDialogue::UDialogue()
{
	NodeType = UDialogueNode::StaticClass();
	EdgeType = UDialogueEdge::StaticClass();

	Color1 = FLinearColor::Red;
	Color2 = FLinearColor::Blue;
	Color3 = FLinearColor::Green;
	Color4 = FLinearColor(0.0f, 1.0f, 1.0f);
	Color5 = FLinearColor(1.0f, 1.0f, 0.0f);
	Color6 = FLinearColor(1.0f, 0.0f, 1.0f);

	Name = "Dialogue";
}

void UDialogue::PrintAllDialogue()
{
	for (int i = 0; i < AllNodes.Num(); i++)
	{
		auto dialogueNode = static_cast<UDialogueNode*>(AllNodes[i]);

		UE_LOG(LogTemp, Warning, TEXT("%i Node: %s "), i, *dialogueNode->DialogueText.ToString());
	}
}

bool UDialogue::UpdateCurrentNode(int ResponseID, ALoopstone_IslandGameState* GameState)
{
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE: CORRECT GAME MODE NOT FOUND"));
		return false;
	}


	// actually finding a new current node
	if (!CurrentDialogueNode)
	{
		// set current to root if none, meaning this is a new conversation
		CurrentDialogueNode = dynamic_cast<UDialogueNode*>(AllNodes[0]);
	}
	else
	{
		// check if the node has that many children, otherwise exit convo
		if (CurrentAvailableOptions.Num() <= ResponseID)
		{
			return false;
		}

		// update current node if available
		auto DialogueNode = dynamic_cast<UDialogueNode*>(CurrentAvailableOptions[ResponseID]->EndNode);
		if (DialogueNode)
		{
			// todo make conditions a separate function
			// CHECK CONDITIONS

			for (auto Element : DialogueNode->EventBoolsConditions)
			{
				// if any element doesn't match the library it shouldn't display
				if (Element.Value != GameState->bEventHasBeenTriggered[static_cast<int>(Element.Key)])
				{
					return false;
				}
			}
			for (auto Element : DialogueNode->TopicBoolsConditions)
			{
				// if any element doesn't match the library it shouldn't display
				if (Element.Value != GameState->bTopicHasBeenRevealed[static_cast<int>(Element.Key)])
				{
					return false;
				}
			}

			if (DialogueNode->TimeOfDayCondition != ETimeOfDay::None &&
				DialogueNode->TimeOfDayCondition != GameState->CurrentTimeOfDay)
			{
				return false;
			}
			if (DialogueNode->ActiveStoryCondition != EStory::None &&
				DialogueNode->ActiveStoryCondition != GameState->CurrentStory)
			{
				return false;
			}

			// only happens if dialogue passes all conditions
			CurrentDialogueNode = DialogueNode;
		}
	}

	// update current options
	CurrentAvailableOptions.Empty();
	for (auto EdgeToCheck : CurrentDialogueNode->Edges)
	{
		UDialogueEdge* DialogueEdge = dynamic_cast<UDialogueEdge*>(EdgeToCheck.Value);
		bool Visible = true;

		// todo make conditions a separate function
		// CHECK CONDITIONS
		for (auto EventCondition : DialogueEdge->EventBoolsConditions)
		{
			// if any element doesn't match the library it should be skipped
			if (EventCondition.Value != GameState->bEventHasBeenTriggered[static_cast<int>(EventCondition.Key)])
			{
				Visible = false;
			}
		}
		for (auto TopicCondition : DialogueEdge->TopicBoolsConditions)
		{
			// if any element doesn't match the library it should be skipped
			if (TopicCondition.Value != GameState->bTopicHasBeenRevealed[static_cast<int>(TopicCondition.Key)])
			{
				Visible = false;
			}
		}

		if (DialogueEdge->TimeOfDayCondition != ETimeOfDay::None &&
			DialogueEdge->TimeOfDayCondition != GameState->CurrentTimeOfDay)
		{
			Visible = false;
		}
		if (DialogueEdge->ActiveStoryCondition != EStory::None &&
			DialogueEdge->ActiveStoryCondition != GameState->CurrentStory)
		{
			Visible = false;
		}

		if (Visible)
		{
			CurrentAvailableOptions.Add(DialogueEdge);
		}
	}

	FString DialogueText = CurrentDialogueNode->DialogueText.ToString();

	// see if it should do recusive checking	

	if (DialogueText == "EXIT")
	{
		return false;
	}
	else if (DialogueText == "CONDITION")
	{
		// if end node
		if (CurrentAvailableOptions.Num() == 0)
		{
			return false;
		}
		// runs until an acceptable child is found
		for (int i = 0; i < CurrentAvailableOptions.Num(); i++)
		{
			if (UpdateCurrentNode(i, GameState))
			{
				break;
			}
		}
	}

	return true;
}

void UDialogue::UpdateEventLibaryBasedOnCurrentNode(ALoopstone_IslandGameState* GameState)
{
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE: CORRECT GAME MODE NOT FOUND"));
		return;
	}

	// todo make this code pretty
	// CHANGE GAME STATE
	if (CurrentDialogueNode)
	{
		for (auto Element : CurrentDialogueNode->EventBoolsToChange)
		{
			GameState->TriggerEvent(Element.Key, Element.Value);
		}
		for (auto Element2 : CurrentDialogueNode->TopicBoolsToChange)
		{
			GameState->bTopicHasBeenRevealed[static_cast<int>(Element2.Key)] = Element2.Value;
			// GameState->bEventHasBeenTriggered[static_cast<int>(Element.Key)] = Element.Value;
		}

		if (CurrentDialogueNode->TimeOfDayChange != ETimeOfDay::None)
		{
			GameState->ChangeTimeOfDay(CurrentDialogueNode->TimeOfDayChange);
			// do other stuff to change day??
		}
		if (CurrentDialogueNode->ActiveStoryChange != EStory::None)
		{
			GameState->ChangeStory(CurrentDialogueNode->ActiveStoryChange);
			// do other stuff to change story??
		}
	}
}

#undef LOCTEXT_NAMESPACE
