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

	switch (NodeColor)
	{
	case EBackgroundColor::Color1:
		return Graph->Color1;
	case EBackgroundColor::Color2:
		return Graph->Color2;
	case EBackgroundColor::Color3:
		return Graph->Color3;
	case EBackgroundColor::Color4:
		return Graph->Color4;
	case EBackgroundColor::Color5:
		return Graph->Color5;
	case EBackgroundColor::Color6:
		return Graph->Color6;
	default:
		return FLinearColor::Black;
	}
}

#endif

#undef LOCTEXT_NAMESPACE
