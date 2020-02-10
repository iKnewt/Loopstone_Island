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
	for (auto& Button : Buttons)
	{
		// UE_LOG(LogTemp, Warning, TEXT("SETTING BUTTON VISIBILITY"))
			Button->SetVisibility(ESlateVisibility::Hidden);
	}
	//font still not set
	FullDialogue = InDialogue;
	FullDialogueInChars = FullDialogue.GetCharArray();
	DialogueCharIndex = 0;
	this->Dialogue = "";
	Responses = InResponses;
	// UE_LOG(LogTemp, Warning, TEXT("SETTING DIALOGUE"))
		float TextSpeedChecker = TextSpeed;
	if(TextSpeedChecker < 0.00001f)
	{
		TextSpeedChecker = 0.03f;
	}
	bCurrentlyWriting = true;
	GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UDialogueWidget::AppendDialogueString, TextSpeedChecker,true);
}

void UDialogueWidget::SetSpeakerName(FText Name) const
{
	Speaker_Name->SetText(Name);
}

bool UDialogueWidget::Initialize()
{
	bool init = Super::Initialize();
	Button_Option0->OnClicked.AddDynamic(this, &UDialogueWidget::onOption0Pressed);
	Button_Option1->OnClicked.AddDynamic(this, &UDialogueWidget::onOption1Pressed);
	Button_Option2->OnClicked.AddDynamic(this, &UDialogueWidget::onOption2Pressed);
	Button_Option3->OnClicked.AddDynamic(this, &UDialogueWidget::onOption3Pressed);
	Button_Option4->OnClicked.AddDynamic(this, &UDialogueWidget::onOption4Pressed);

	GameState = reinterpret_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState());
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE WIDGET: CORRECT GAME MODE NOT FOUND"));
	}

	return init;
}

void UDialogueWidget::AppendDialogueString()
{
	Dialogue.AppendChar(FullDialogueInChars[DialogueCharIndex]);
	Dialogue_Text->SetText(FText::FromString(Dialogue));
	if (FullDialogueInChars.Num() == DialogueCharIndex +1)
	{
		GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
		// UE_LOG(LogTemp, Warning, TEXT("DONE"))
			RevealOptions();
		bCurrentlyWriting = false;
	}
	else
	{
		DialogueCharIndex++;
	}
}

void UDialogueWidget::RevealOptions()
{
	for (int i = 0; i < Responses.Num(); i++)
	{
		// UE_LOG(LogTemp, Warning, TEXT("SETTING stuff"))
		Options[i]->SetText(FText::FromString(Responses[i]));
		Buttons[i]->SetVisibility(ESlateVisibility::Visible);
	}
}
