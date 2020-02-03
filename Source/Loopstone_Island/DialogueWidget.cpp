// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "TimerManager.h"
#include "Components/Button.h"

void UDialogueWidget::SetDialogueWithOptions(float TextSpeed, FString InDialogue, TArray<FString> InResponses, UFont* Font)
{
	if(Buttons.Num() == 0)
	{
		Buttons.Add(Button_Option0);
		Buttons.Add(Button_Option1);
		Buttons.Add(Button_Option2);
		Buttons.Add(Button_Option3);
		Buttons.Add(Button_Option4);

		Options.Add(Option_0);
		Options.Add(Option_1);
		Options.Add(Option_2);
		Options.Add(Option_3);
		Options.Add(Option_4);
	}
	//font still not set
	FullDialogue = InDialogue;
	FullDialogueInChars = FullDialogue.GetCharArray();
	DialogueCharIndex = 0;
	this->Dialogue = "";
	Responses = InResponses;
	UE_LOG(LogTemp, Warning, TEXT("SETTING DIALOGUE"))
	GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UDialogueWidget::AppendDialogueString, TextSpeed,true);
}

void UDialogueWidget::AppendDialogueString()
{
	UE_LOG(LogTemp, Warning, TEXT("APPENDING"))
	Dialogue.AppendChar(FullDialogueInChars[DialogueCharIndex]);
	Dialogue_Text->SetText(FText::FromString(Dialogue));
	if (FullDialogueInChars.Num() == DialogueCharIndex +1)
	{
		GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("DONE"))
			RevealOptions();
	}
	else
	{
		DialogueCharIndex++;
	}
}

void UDialogueWidget::RevealOptions()
{
	for (auto& Button : Buttons)
	{
		UE_LOG(LogTemp, Warning, TEXT("SETTING BUTTON VISIBILITY"))
		Button->SetVisibility(ESlateVisibility::Visible);
	}
	for (int i = 0; i < Responses.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("SETTING stuff"))
		Options[i]->SetText(FText::FromString(Responses[i]));
		Buttons[i]->SetVisibility(ESlateVisibility::Visible);
	}
	Button_Option0->SetVisibility(ESlateVisibility::Visible);
}
