// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "TimerManager.h"

void UDialogueWidget::SetDialogueWithOptions(float TextSpeed, FString InDialogue, UFont* Font)
{
	//font still not set
	FullDialogue = InDialogue;
	FullDialogueInChars = FullDialogue.GetCharArray();
	DialogueCharIndex = 0;
	this->Dialogue = "";
	UE_LOG(LogTemp, Warning, TEXT("SETTING DIALOGUE"))
	GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UDialogueWidget::AppendDialogueString, TextSpeed,true);
}

void UDialogueWidget::AppendDialogueString()
{
	UE_LOG(LogTemp, Warning, TEXT("APPENDING"))
	Dialogue.AppendChar(FullDialogueInChars[DialogueCharIndex]);
	if (FullDialogueInChars.Num() == DialogueCharIndex +1)
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
