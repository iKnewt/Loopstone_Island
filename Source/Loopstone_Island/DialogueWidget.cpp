// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "TimerManager.h"

void UDialogueWidget::SetDialogueWithOptions(float TextSpeed, FString InDialogue)
{
	FullDialogue = InDialogue;
	FullDialogueInChars = FullDialogue.GetCharArray();
	DialogueCharIndex = 0;
	this->Dialogue = "";
	GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UDialogueWidget::AddLetterToDialogue, TextSpeed);
}

void UDialogueWidget::AppendDialogueString()
{
	UE_LOG(LogTemp, Warning, TEXT("APPENDING"))
	Dialogue.AppendChar(FullDialogueInChars[DialogueCharIndex]);
	if (FullDialogueInChars.Num() > DialogueCharIndex)
	{
		GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("DONE"))
	}
	else
	{
		DialogueCharIndex++;
	}
	SetCurrentDialogueText();
}
