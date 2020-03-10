// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "TimerManager.h"
#include "Components/Button.h"
#include "WidgetBlueprintLibrary.h"
#include "Dialogue/Dialogue.h"
#include "Dialogue/DialogueNode.h"

void UDialogueWidget::SetupButtonStyles()
{
}

void UDialogueWidget::SetDialogueWithOptions(float TextSpeed, FString InDialogue, TArray<FString> InResponses,
                                             UFont* Font)
{
	if (Buttons.Num() == 0)
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

	Button_Option000->SetVisibility(ESlateVisibility::Visible);
	NextOption->SetVisibility(ESlateVisibility::Hidden);
	
	//font still not set
	FullDialogue = InDialogue;
	FullDialogueInChars = FullDialogue.GetCharArray();
	DialogueCharIndex = 0;
	this->Dialogue = "";
	Responses = InResponses;
	// UE_LOG(LogTemp, Warning, TEXT("SETTING DIALOGUE"))
	float TextSpeedChecker = TextSpeed;
	if (TextSpeedChecker < 0.00001f)
	{
		TextSpeedChecker = 0.03f;
	}
	bCurrentlyWriting = true;
	GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UDialogueWidget::AppendDialogueString,
	                                       TextSpeedChecker, true);
}

void UDialogueWidget::SetSpeakerName(FString Name) const
{
	Speaker_Name->SetText(FText::FromString(Name));
}

void UDialogueWidget::SetRichStyleText(UDataTable* RichStyleTable) const
{
	Dialogue_Text->SetTextStyleSet(RichStyleTable);
}

void UDialogueWidget::updateButtonLookOnFocus()
{
	for(auto Button : Buttons)
	{
		if(Button->HasAnyUserFocus())
		{
			Button->SetStyle(Button_FocusedStyle->WidgetStyle);
		}
		else
		{
			Button->SetStyle(Button_NormalStyle->WidgetStyle);
		}
	}
}

void UDialogueWidget::FocusOnOptions()
{
	Button_Option0->SetKeyboardFocus();
}

void UDialogueWidget::onOption000Pressed()
{
	if(bCurrentlyWriting)
	{
		GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UDialogueWidget::AppendDialogueString,
			0.001f, true);
	}
	else
	{
		GameState->UpdateDialogueBasedOnResponse(0);
	}

}

void UDialogueWidget::onOption0Pressed()
{
	GameState->UpdateDialogueBasedOnResponse(1);
}

void UDialogueWidget::onOption1Pressed()
{
	GameState->UpdateDialogueBasedOnResponse(2);
}

void UDialogueWidget::onOption2Pressed()
{
	GameState->UpdateDialogueBasedOnResponse(3);
}

void UDialogueWidget::onOption3Pressed()
{
	GameState->UpdateDialogueBasedOnResponse(4);
}

void UDialogueWidget::onOption4Pressed()
{
	GameState->UpdateDialogueBasedOnResponse(5);
}

bool UDialogueWidget::Initialize()
{
	bool init = Super::Initialize();

	Button_Option000->OnClicked.AddDynamic(this, &UDialogueWidget::onOption000Pressed);

	Button_Option0->OnClicked.AddDynamic(this, &UDialogueWidget::onOption0Pressed);
	Button_Option1->OnClicked.AddDynamic(this, &UDialogueWidget::onOption1Pressed);
	Button_Option2->OnClicked.AddDynamic(this, &UDialogueWidget::onOption2Pressed);
	Button_Option3->OnClicked.AddDynamic(this, &UDialogueWidget::onOption3Pressed);
	Button_Option4->OnClicked.AddDynamic(this, &UDialogueWidget::onOption4Pressed);

	// GameState = reinterpret_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState());
	GameState = dynamic_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState());
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE WIDGET: CORRECT GAME MODE NOT FOUND"));
	}

	return init;
}

void UDialogueWidget::AppendDialogueString()
{

	// testing rich text
	if (FullDialogueInChars[DialogueCharIndex] == '<')
	{
		bHighlightText = true;
		Dialogue.Append("<Highlight>");
		Dialogue.Append("</>");
	}
	else if (FullDialogueInChars[DialogueCharIndex] == '>')
	{
		bHighlightText = false;
	}
	else
	{
		if (bHighlightText)
		{
			Dialogue.InsertAt(Dialogue.Len() - 3, FullDialogueInChars[DialogueCharIndex]);
		}
		else
		{
			Dialogue.AppendChar(FullDialogueInChars[DialogueCharIndex]);
		}
	}

	// Dialogue_Text->SetFont(FSlateFontInfo())
	Dialogue_Text->SetText(FText::FromString(Dialogue));

	if (FullDialogueInChars.Num() == DialogueCharIndex + 1)
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
	if (Responses.Num() == 0)
	{
		NextOption->SetVisibility(ESlateVisibility::Visible);
		Button_Option000->SetKeyboardFocus();
		GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
	}
	else
	{
		Button_Option000->SetVisibility(ESlateVisibility::Hidden);
		// Button_Option0->SetKeyboardFocus();
		Button_MouseStyle->SetKeyboardFocus();
		GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UDialogueWidget::updateButtonLookOnFocus,
			0.005f, true);
	}

	// We have a limit of 5 responses in the GUI, so check to make sure we don't try to access outside available buttons
	int	NumberOfResponses = Responses.Num();
	if (NumberOfResponses > 5)
	{
		NumberOfResponses = 5;
	}
	
	for (int i = 0; i < NumberOfResponses; i++)
	{
		// UE_LOG(LogTemp, Warning, TEXT("SETTING stuff"))
		Options[i]->SetText(FText::FromString(Responses[i]));
		Buttons[i]->SetVisibility(ESlateVisibility::Visible);
	}

	GameState->CurrentIslander->ChangeMouthExpression(GameState->CurrentDialogue->CurrentDialogueNode->MouthExpression);
	RevealOptionsAnimation();
}
