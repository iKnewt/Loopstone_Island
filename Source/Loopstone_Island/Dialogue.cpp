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
			// only happens if dialogue passes all conditions
			CurrentDialogueNode = DialogueNode;
		}
	}

	// todo remove from this class or at least do a check
	// if (CurrentIslander)
	// {
	// 	CurrentIslander->ChangeEyeExpression(CurrentDialogueNode->RightEyeExpression,
	// 	                                     CurrentDialogueNode->LeftEyeExpression);
	// 	CurrentIslander->ChangeMouthExpression(CurrentDialogueNode->MouthExpression);
	// }

	// update current options
	CurrentAvailableOptions.Empty();
	for (auto EdgeToCheck : CurrentDialogueNode->Edges)
	{
		UDialogueEdge* DialogueEdge = dynamic_cast<UDialogueEdge*>(EdgeToCheck.Value);
		bool Visible = true;
		// check for conditions  conditions
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

	if (CurrentDialogueNode)
	{
		for (auto Element : CurrentDialogueNode->EventBoolsToChange)
		{
			// if (GameState->TriggerEvent(Element.Key, Element.Value))
			// {
			// }
			GameState->bEventHasBeenTriggered[static_cast<int>(Element.Key)] = Element.Value;
		}
		for (auto Element2 : CurrentDialogueNode->TopicBoolsToChange)
		{

			GameState->bTopicHasBeenRevealed[static_cast<int>(Element2.Key)] = Element2.Value;
			// GameState->bEventHasBeenTriggered[static_cast<int>(Element.Key)] = Element.Value;
		}
	}
}

#undef LOCTEXT_NAMESPACE
