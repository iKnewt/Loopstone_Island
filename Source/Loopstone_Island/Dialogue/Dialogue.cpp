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


void UDialogue::UpdateCurrentOptions(ALoopstone_IslandGameState* GameState)
{
	// update current options
	CurrentAvailableEdges.Empty();
	for (auto EdgeToCheck : CurrentDialogueNode->Edges)
	{
		UDialogueEdge* DialogueEdge = UE4Casts_Private::DynamicCast<UDialogueEdge*>(EdgeToCheck.Value);
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
			break;
		}
	default: ;
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
			if (CurrentDialogueNode->ConditionsMet(GameState))
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
			if (CurrentDialogueNode->ConditionsMet(GameState))
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
			if (CurrentDialogueNode->ConditionsMet(GameState))
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
			if (CurrentDialogueNode->ConditionsMet(GameState))
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
