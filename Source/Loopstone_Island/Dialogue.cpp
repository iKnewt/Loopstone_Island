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

	Name = "Dialogue";
}

#undef LOCTEXT_NAMESPACE