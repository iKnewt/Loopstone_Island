// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue.h"
#include "DialogueNode.h"
#include "DialogueEdge.h"
#include "UObject/Class.h"
#include "Loopstone_IslandGameModeBase.h"

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

bool UDialogue::UpdateCurrentNode(int ResponseID)
{
	GameMode = dynamic_cast<ALoopstone_IslandGameModeBase*>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("CORRECT GAME MODE NOT FOUND"));
		return false;
	}
	
	if (!CurrentDialogueNode)
	{
		// set current to root if none
		CurrentDialogueNode = dynamic_cast<UDialogueNode*>(AllNodes[0]);
	}
	else
	{
		// update current node if available
		auto CurrentDialogueNodeToCheck = dynamic_cast<UDialogueNode*>(CurrentAvailableOptions[ResponseID]->EndNode);
		if (CurrentDialogueNodeToCheck)
		{
			for (auto Element : CurrentDialogueNodeToCheck->EventBoolsConditions)
			{
				// should check if gamemode is valid
				// if any element doesn't match the library it shouldn't display
				if (Element.Value != GameMode->bEventHasBeenTriggered[static_cast<int>(Element.Key)])
				{
					return false;
				}
			}
			// only happens if dialogue passes all conditions
			// CurrentDialogueNode = dynamic_cast<UDialogueNode*>(CurrentAvailableOptions[ResponseID]->EndNode);
			CurrentDialogueNode = CurrentDialogueNodeToCheck;
		}
	}

	// todo remove from this class or at least do a check
	if (CurrentIslander)
	{
		CurrentIslander->ChangeEyeExpression(CurrentDialogueNode->RightEyeExpression,
		                                     CurrentDialogueNode->LeftEyeExpression);
		CurrentIslander->ChangeMouthExpression(CurrentDialogueNode->MouthExpression);
	}

	// update current options
	CurrentAvailableOptions.Empty();
	for (auto Element : CurrentDialogueNode->Edges)
	{
		// check for conditions  conditions
		UDialogueEdge* temp = dynamic_cast<UDialogueEdge*>(Element.Value);

		// if temp is acceptable
		CurrentAvailableOptions.Add(temp);
	}

	return true;
}

void UDialogue::UpdateEventLibaryBasedOnCurrentNode()
{
	if (CurrentDialogueNode)
	{
		for (auto Element : CurrentDialogueNode->EventBoolsToChange)
		{
			if (GameMode->TriggerEvent(Element.Key, Element.Value))
			{
			}
			// EventLibrary->bEventHasBeenTriggered[static_cast<int>(Element.Key)] = Element.Value;
		}
	}
}

#undef LOCTEXT_NAMESPACE
