// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueNode.h"
#include "Dialogue.h"

#define LOCTEXT_NAMESPACE "DialogueNode"

UDialogueNode::UDialogueNode()
{
#if WITH_EDITORONLY_DATA
	CompatibleGraphType = UDialogue::StaticClass();

	ContextMenuName = LOCTEXT("ContextMenuName", "Dialogue Node");
#endif
}

#if WITH_EDITOR

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

	switch (DialoguerPosition)
	{
	case EDialoguerPosition::Left:
		return Graph->LeftDialogueBgColor;
	case EDialoguerPosition::Right:
		return Graph->RightDialogueBgColor;
	default:
		return FLinearColor::Black;
	}
}

#endif

#undef LOCTEXT_NAMESPACE
