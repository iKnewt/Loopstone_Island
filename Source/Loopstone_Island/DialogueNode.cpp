// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueNode.h"
#include "Dialogue.h"
#include "DialogueEdge.h"

#define LOCTEXT_NAMESPACE "DialogueNode"

UDialogueNode::UDialogueNode()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UDialogue::StaticClass();

	ContextMenuName = LOCTEXT("ContextMenuName", "Dialogue Node");
#endif
}

#if WITH_EDITOR

void UDialogueNode::PrintSelfAndChildren()
{
	UE_LOG(LogTemp, Warning, TEXT("Node: %s "), *DialogueText.ToString());
	for (auto Element : Edges)
	{
		UDialogueEdge* temp = dynamic_cast<UDialogueEdge*>(Element.Value);
		UE_LOG(LogTemp, Warning, TEXT("Edge: %s "), *temp->OptionText);
		UDialogueNode* temp2 = dynamic_cast<UDialogueNode*>(Element.Key);
		temp2->PrintSelfAndChildren();
	}
}

bool UDialogueNode::ConditionsMet(ALoopstone_IslandGameState* GameState)
{
	for (auto Element : EventBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != GameState->bEventHasBeenTriggered[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}
	for (auto Element : TopicBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != GameState->bTopicHasBeenRevealed[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}
	
	// if the time of day doesn't match condition
	if (TimeOfDayCondition != ETimeOfDay::None &&
		TimeOfDayCondition != GameState->CurrentTimeOfDay)
	{
		return false;
	}
	if (ActiveStoryCondition != EStory::None &&
		ActiveStoryCondition != GameState->CurrentStory)
	{
		return false;
	}


	// if all conditions are met
	return true;
}

FText UDialogueNode::GetNodeTitle() const
{
	return DialogueText.IsEmpty() ? LOCTEXT("EmptyDialogueText", "No Dialogue Text") : DialogueText;
}

void UDialogueNode::SetNodeTitle(const FText& NewTitle)
{
	DialogueText = NewTitle;
}

FLinearColor UDialogueNode::GetBackgroundColor() const
{
	UDialogue* Graph = Cast<UDialogue>(GetGraph());

	if (!Graph)
	{
		return Super::GetBackgroundColor();
	}

	switch (NodeExits)
	{
	case ENodeExits::NoOptions:
		return Graph->Color1;
	case ENodeExits::OptionsWithExit:
		return Graph->Color2;
	case ENodeExits::Exit:
		return Graph->Color3;
	case ENodeExits::ReturnToLastOptionsWithExit:
		return Graph->Color4;
	case ENodeExits::Options:
		return Graph->Color5;
	case ENodeExits::Condition:
		return Graph->Color6;
	default:
		return FLinearColor::Black;
	}
}

#endif

#undef LOCTEXT_NAMESPACE
