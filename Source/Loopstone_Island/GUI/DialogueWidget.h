// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Font.h"
#include "TextBlock.h"
#include "RichTextBlock.h"
#include "Characters/PlayerCharacter.h"
#include "Loopstone_IslandGameState.h"
#include "SButton.h"
#include "Widgets/Input/SButton.h"
#include "VerticalBox.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUsingController = false;
	
	// Test invisible button
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Option000;

	// todo MAKE THIS BETTER BECAUSE I HATE THIS SO MUCH
	UPROPERTY(meta = (BindWidget))
	UButton* Button_MouseStyle;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_UnFocusedStyle;
	UPROPERTY(meta = (BindWidget))
	UButton* Button_FocusedStyle;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_MouseBlocker;
	UButton* LastFocused;

	void SetupButtonStyles();

	UPROPERTY()
	ALoopstone_IslandGameState* GameState = nullptr;

	/**
	 * The function that starts it all.
	 * Send in dialogue and options for the specific dialogue option, and this will set it up 
	 */
	UFUNCTION(BlueprintCallable)
	void SetDialogueWithOptions(float TextSpeed, FString InDialogue, TArray<FString> InResponses,
	                            UFont* Font = nullptr);
	/**
	 * Sets the speaker's name.
	 * Should be run whenever a new islander speaks.
	 */
	UFUNCTION(BlueprintCallable)
	void SetSpeakerName(FString Name) const;
	void SetRichStyleText(UDataTable* RichStyleTable) const;

	UFUNCTION(BlueprintCallable)
	void updateButtonLookOnFocus();

	UFUNCTION(BlueprintCallable)
	void FocusOnOptions();

	UFUNCTION()
	void onOption000Pressed();
	UFUNCTION()
	void onOption0Pressed();
	UFUNCTION()
	void onOption1Pressed();
	UFUNCTION()
	void onOption2Pressed();
	UFUNCTION()
	void onOption3Pressed();
	UFUNCTION()
	void onOption4Pressed();

	UFUNCTION()
	void onMouseBlockerPressed();

	//Dialogue Text
	UPROPERTY(meta = (BindWidget))
	URichTextBlock* Dialogue_Text;

	UFUNCTION(BlueprintImplementableEvent)
	void RevealOptionsAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDialogueAnimation(bool Forwards);

	UFUNCTION()
		void SetupForInput();
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateIsUsingControllerFromGameInstance();
	

protected:

	bool Initialize() override;
private:
	void AddLetterToDialogue()
	{
	}

	FString Dialogue = "helo";
	TArray<wchar_t> FullDialogueInChars;
	FString FullDialogue = "helo fren";
	int32 DialogueCharIndex = 0;
	TArray<FString> Responses;
	UFont* DialogueFont = nullptr;

	bool bCurrentlyWriting = false;
	bool bHighlightText = false;

	/**
	 * adds a character onto the Dialogue string that's written. Used to create the writing text animation.
	 */
	void AppendDialogueString();

	void RevealOptions();

	// // Test invisible button
	// UPROPERTY(meta = (BindWidget))
	// UButton* Button_Option000;

	//Buttons
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_44;

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

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NextOption;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* Speaker_Name;
	UPROPERTY()
	TArray<UButton*> Buttons;
	UPROPERTY()
	TArray<UTextBlock*> Options;

	FTimerHandle DialogueTimerHandle;

	int Index = 0;
};
