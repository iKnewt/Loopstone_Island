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

#if WITH_EDITOR

FText UDialogueNode::GetNodeTitle() const
{
	return DialogueText.IsEmpty() ? LOCTEXT("EmptyDialogueText", "...") : DialogueText;
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
		return FLinearColor::Black;
	case ENodeExits::OptionsWithExit:
		return FLinearColor::Red;
	case ENodeExits::ReturnToLastOptionsWithExit:
		return FLinearColor(1, 0.4, 0.2);
	case ENodeExits::Options:
		return FLinearColor(1, 1, 0);
	case ENodeExits::Condition:
		return FLinearColor(0.13, 1, 0.4);
	case ENodeExits::ReturnToRoot:
		return FLinearColor::Blue;
	default:
		return FLinearColor::White;
	}
}

bool UDialogueNode::CanEditChange(const UProperty* InProperty) const
{
	const bool ParentVal = Super::CanEditChange(InProperty);

	// // Can we edit flower color?
	// if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDialogueNode, FlowerColor))
	// {
	// 	return PlantType == EPlantType::Flower;
	// }
	//
	// // Can we edit food amount?
	// if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDialogueNode, FoodAmount))
	// {
	// 	return PlantType == EPlantType::Food;
	// }
	//
	// // Can we edit poison amount?
	// if (InProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UDialogueNode, PoisonDamagePerSecond))
	// {
	// 	return PlantType == EPlantType::Poison;
	// }
	//
	return ParentVal;
}

#endif

#undef LOCTEXT_NAMESPACE
