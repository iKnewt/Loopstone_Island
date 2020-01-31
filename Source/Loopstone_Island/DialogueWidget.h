// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Engine/Font.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Dialogue = "helo";
	TArray<wchar_t> FullDialogueInChars;
	FString FullDialogue = "helo fren";

	int32 DialogueCharIndex = 0;

	UFont* DialogueFont = nullptr;

	/**
	 * The function that starts it all.
	 * Send in dialogue and options for the specific dialogue option, and this will set it up 
	 */
	UFUNCTION(BlueprintCallable)
		void SetDialogueWithOptions(float TextSpeed, FString InDialogue, UFont* Font = nullptr);

	/**
	 * adds a character onto the Dialogue string that's written. Used to create the writing text animation.
	 */
	void AppendDialogueString();

	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetCurrentDialogueText();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void RevealOptions();

private:
	void AddLetterToDialogue(){}

	FTimerHandle DialogueTimerHandle;



};
