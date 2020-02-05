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

	if (root->ChildrenNodes.Num() == 0)
	{
		
	}
	

	
}

void UDialogue::GetDialogueText()
{
	
}

void UDialogue::UpdateCurrentNode(int ResponseID)
{
	if(!CurrentDialogueNode)
	{
		CurrentDialogueNode = dynamic_cast<UDialogueNode*>(AllNodes[0]);
	}
	else
	{
		// update current node
		CurrentDialogueNode = dynamic_cast<UDialogueNode*>(CurrentAvailableOptions[ResponseID]->EndNode);
	}

	// todo remove from this class
	if(CurrentIslander)
	{
		CurrentIslander->ChangeEyeExpression(CurrentDialogueNode->RightEyeExpression, CurrentDialogueNode->LeftEyeExpression);
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
}

#undef LOCTEXT_NAMESPACE
