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
	

	
}

#undef LOCTEXT_NAMESPACE
