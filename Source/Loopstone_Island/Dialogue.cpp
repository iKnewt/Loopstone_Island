// Fill out your copyright notice in the Description page of Project Settings.


#include "Dialogue.h"
#include "DialogueNode.h"
#include "DialogueEdge.h"

#define LOCTEXT_NAMESPACE "Dialogue"

UDialogue::UDialogue()
{
	NodeType = UDialogueNode::StaticClass();
	EdgeType = UDialogueEdge::StaticClass();

	LeftDialogueBgColor = FLinearColor::Red;
	RightDialogueBgColor = FLinearColor::Blue;

	// EventLibrary = NewObject<UEventLibrary>();
	bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);

	Name = "Dialogue";
}

bool UDialogue::TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction)
{
	bEventHasBeenTriggered[static_cast<int>(EventType)] = NewBoolValue;

	UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(EventType), (NewBoolValue ? TEXT("true") : TEXT("false")));

	if (RunFunction)
	{
		switch (EventType)
		{
		case EEventType::HasTape:
			break;
		default:
			break;
		}
	}
	return true;
}

void UDialogue::PrintAllDialogue()
{
	for (UGenericGraphNode* RootNode : RootNodes)
	{
		auto dialogueNode = static_cast<UDialogueNode*>(RootNode);

		UE_LOG(LogTemp, Warning, TEXT("Root: %s "), *dialogueNode->DialogueText.ToString());
	}
	//
	// for (UGenericGraphNode* Node : AllNodes)
	// {
	// 	auto dialogueNode = static_cast<UDialogueNode*>(Node);
	//
	// 	UE_LOG(LogTemp, Warning, TEXT("AllNodes: %s "), *dialogueNode->DialogueText.ToString());
	// }

	UDialogueNode* root = dynamic_cast<UDialogueNode*>(AllNodes[0]);
	root->PrintSelfAndChildren();

	if (root->ChildrenNodes.Num() == 0)
	{
	}
}

void UDialogue::GetDialogueText()
{
}

bool UDialogue::UpdateCurrentNode(int ResponseID)
{
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
				// if any element doesn't match the library it shouldn't display
				if (Element.Value == bEventHasBeenTriggered[static_cast<int>(Element.Key)])
				{
					return false;
				}
			}
		// only happens if dialogue passes all conditions
		// CurrentDialogueNode = dynamic_cast<UDialogueNode*>(CurrentAvailableOptions[ResponseID]->EndNode);
		CurrentDialogueNode = CurrentDialogueNodeToCheck;
		}
	}

	// todo remove from this class
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
			if (TriggerEvent(Element.Key, Element.Value))
			{ }
			// EventLibrary->bEventHasBeenTriggered[static_cast<int>(Element.Key)] = Element.Value;
		}
	}
}

#undef LOCTEXT_NAMESPACE
