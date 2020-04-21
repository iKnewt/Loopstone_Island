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

	Name = "Dialogue";
}

void UDialogue::ResetDialogue()
{
	for (int i = 0; i < AllNodes.Num(); i++)
	{
		auto dialogueNode = static_cast<UDialogueNode*>(AllNodes[i]);
		dialogueNode->bHasBeenVisited = false;
		// 	// UE_LOG(LogTemp, Warning, TEXT("%i Node: %s "), i, *dialogueNode->DialogueText.ToString());
	}
}


void UDialogue::UpdateCurrentOptions(ALoopstone_IslandGameState* GameState)
{
	// update current options
	CurrentAvailableEdges.Empty();
	for (auto EdgeToCheck : CurrentDialogueNode->Edges)
	{
		UDialogueEdge* DialogueEdge = UE4Casts_Private::DynamicCast<UDialogueEdge*>(EdgeToCheck.Value);
		if (GameState->ConditionsMet(DialogueEdge->TopicBoolsConditions,
		                             DialogueEdge->EventBoolsConditions,
		                             DialogueEdge->InventoryBoolsConditions,
		                             DialogueEdge->TimeOfDayCondition,
		                             DialogueEdge->ActiveStoryCondition))
		{
			CurrentAvailableEdges.Add(DialogueEdge);
		}
	}
}

TArray<FString> UDialogue::GetCurrentOptions(ALoopstone_IslandGameState* GameState)
{
	UpdateCurrentOptions(GameState);
	TArray<FString> Options;
	switch (CurrentDialogueNode->NodeExits)
	{
	case ENodeExits::OptionsWithExit:
		{
			LastMenuNode = CurrentDialogueNode;
			Options.Add("Good-bye");
			for (auto Option : CurrentAvailableEdges)
			{
				Options.Add(Option->OptionText);
			}
			break;
		}
	case ENodeExits::Options:
		{
			for (auto Option : CurrentAvailableEdges)
			{
				Options.Add(Option->OptionText);
			}
			break;
		}
	default: break;
	}
	return Options;
}

bool UDialogue::UpdateCurrentNode(int ResponseID, ALoopstone_IslandGameState* GameState)
{
	// return true means we print the (hopefully updated) current node
	// return false means close the conversation

	// if the gamestate is no good close conversation
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE: CORRECT GAME STATE NOT FOUND"));
		return false;
	}

	if (!CurrentDialogueNode)
	{
		// set current to root if none, meaning this is a new conversation
		CurrentDialogueNode = dynamic_cast<UDialogueNode*>(AllNodes[0]);
	}

	// collect the available children of the current node
	UpdateCurrentOptions(GameState);

	switch (CurrentDialogueNode->NodeExits)
	{
	case ENodeExits::NoOptions:
		// update next node to be its edge 0 to node
		if (CurrentAvailableEdges.Num() > 0)
		{
			CurrentDialogueNode = static_cast<UDialogueNode*>(CurrentAvailableEdges[0]->EndNode);
			// // // check conditions
			if (CurrentDialogueNodeConditionsMet(GameState))
			{
				// the current node is the one we want, no options needed
				return true;
			}
			else
			{
				// recursively check the next child node
				return UpdateCurrentNode(0, GameState);
			}
		}
		else
		{
			return false;
		}
		break;
	case ENodeExits::OptionsWithExit:

		// the player went with exit no new node, close dialogue
		if (ResponseID <= 1)
		{
			CurrentDialogueNode = nullptr;
			return false;
		}


		if (CurrentAvailableEdges.Num() > 0)
		{
			CurrentDialogueNode = static_cast<UDialogueNode*>(CurrentAvailableEdges[ResponseID - 2]->EndNode);
			// // // check conditions
			if (CurrentDialogueNodeConditionsMet(GameState))
			{
				// the current node is the one we want, no options needed
				// CurrentOptionsToDisplay.Add("Good-bye");
				return true;
			}
			else
			{
				// recursively check the next child node
				return UpdateCurrentNode(0, GameState);
			}
		}
		else
		{
			return false;
		}
		break;
	case ENodeExits::ReturnToLastOptionsWithExit:
		if (LastMenuNode)
		{
			CurrentDialogueNode = LastMenuNode;
			return true;
		}
		else
		{
			return false;
		}
		break;
	case ENodeExits::Options:

		// the player went with exit no new node, close dialogue
		if (ResponseID == 0)
		{
			CurrentDialogueNode = nullptr;
			return false;
		}

		if (CurrentAvailableEdges.Num() > 0)
		{
			CurrentDialogueNode = static_cast<UDialogueNode*>(CurrentAvailableEdges[ResponseID - 1]->EndNode);
			// // // check conditions
			if (CurrentDialogueNodeConditionsMet(GameState))
			{
				// the current node is the one we want
				return true;
			}
			else
			{
				// recursively check the next child node
				return UpdateCurrentNode(0, GameState);
			}
		}
		else
		{
			return false;
		}
		break;
	case ENodeExits::Condition:
		// set current to root if none, meaning this is a new conversation
		// go through the children of the root until a valid is found
		for (int i = 0; i < CurrentAvailableEdges.Num(); i++)
		{
			CurrentDialogueNode = static_cast<UDialogueNode*>(CurrentAvailableEdges[i]->EndNode);
			if (CurrentDialogueNodeConditionsMet(GameState))
			{
				// the current node is the one we want, no options needed
				return true;
			}
		}
		return false;
		break;
	case ENodeExits::ReturnToRoot:
		CurrentDialogueNode = dynamic_cast<UDialogueNode*>(AllNodes[0]);
		return UpdateCurrentNode(0, GameState);
		break;
	case ENodeExits::None:
		break;
	default: ;
	}

	return false;
}

bool UDialogue::CurrentDialogueNodeConditionsMet(ALoopstone_IslandGameState* GameState)
{
	return GameState->ConditionsMet(CurrentDialogueNode->TopicBoolsConditions,
	                                CurrentDialogueNode->EventBoolsConditions,
	                                CurrentDialogueNode->InventoryBoolsConditions,
	                                CurrentDialogueNode->TimeOfDayCondition,
	                                CurrentDialogueNode->ActiveStoryCondition);
}

#undef LOCTEXT_NAMESPACE
