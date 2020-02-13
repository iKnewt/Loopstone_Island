// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Font.h"
#include "TextBlock.h"
#include "PlayerCharacter.h"
#include "Loopstone_IslandGameState.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class LOOPSTONE_ISLAND_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
	ALoopstone_IslandGameState* GameState = nullptr;
	
	/**
	 * The function that starts it all.
	 * Send in dialogue and options for the specific dialogue option, and this will set it up 
	 */
	UFUNCTION(BlueprintCallable)
		void SetDialogueWithOptions(float TextSpeed, FString InDialogue, TArray<FString> InResponses, UFont* Font = nullptr);
	/**
	 * Sets the speaker's name.
	 * Should be run whenever a new islander speaks.
	 */
	UFUNCTION(BlueprintCallable)
		void SetSpeakerName(FString Name) const;

	

	UFUNCTION()
	void onOption000Pressed();


	UFUNCTION()
	void onOption0Pressed()
	{
		GameState->UpdateDialogueBasedOnResponse(1);
	}
	UFUNCTION()
	void onOption1Pressed()
	{
		GameState->UpdateDialogueBasedOnResponse(2);
	}
	UFUNCTION()
	void onOption2Pressed()
	{
		GameState->UpdateDialogueBasedOnResponse(3);
	}
	UFUNCTION()
	void onOption3Pressed()
	{
		GameState->UpdateDialogueBasedOnResponse(4);
	}
	UFUNCTION()
	void onOption4Pressed()
	{
		GameState->UpdateDialogueBasedOnResponse(5);
	}


	
protected:
	
	bool Initialize() override;
private:
	void AddLetterToDialogue(){}
	FString Dialogue = "helo";
	TArray<wchar_t> FullDialogueInChars;
	FString FullDialogue = "helo fren";
	int32 DialogueCharIndex = 0;
	TArray<FString> Responses;
	UFont* DialogueFont = nullptr;

	bool bCurrentlyWriting = false;

	/**
	 * adds a character onto the Dialogue string that's written. Used to create the writing text animation.
	 */
	void AppendDialogueString();

	void RevealOptions();

	// Test invisible button
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Option000;
	
	//Buttons
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Option0;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Option1;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Option2;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Option3;
	UPROPERTY(meta = (BindWidget))
		UButton* Button_Option4;

	//Text for Buttons

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Option_0;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Option_1;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Option_2;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Option_3;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Option_4;

	//Dialogue Text
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Dialogue_Text;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Speaker_Name;

	UPROPERTY()
		TArray<UButton*> Buttons;
	UPROPERTY()
		TArray<UTextBlock*> Options;

	FTimerHandle DialogueTimerHandle;



};
