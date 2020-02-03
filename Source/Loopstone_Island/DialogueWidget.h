// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Font.h"
#include "TextBlock.h"
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

	/**
	 * The function that starts it all.
	 * Send in dialogue and options for the specific dialogue option, and this will set it up 
	 */
	UFUNCTION(BlueprintCallable)
		void SetDialogueWithOptions(float TextSpeed, FString InDialogue, TArray<FString> InResponses, UFont* Font = nullptr);
	UFUNCTION()
	void onOption0Pressed(){ UE_LOG(LogTemp, Warning, TEXT("SIGNAL 1")) }
	UFUNCTION()
	void onOption1Pressed(){ UE_LOG(LogTemp, Warning, TEXT("SIGNAL 2")) }
	UFUNCTION()
	void onOption2Pressed(){ UE_LOG(LogTemp, Warning, TEXT("SIGNAL 3")) }
	UFUNCTION()
	void onOption3Pressed(){ UE_LOG(LogTemp, Warning, TEXT("SIGNAL 4")) }
	UFUNCTION()
	void onOption4Pressed(){ UE_LOG(LogTemp, Warning, TEXT("SIGNAL 5")) }
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

	/**
	 * adds a character onto the Dialogue string that's written. Used to create the writing text animation.
	 */
	void AppendDialogueString();

	void RevealOptions();

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

	UPROPERTY()
		TArray<UButton*> Buttons;
	UPROPERTY()
		TArray<UTextBlock*> Options;

	FTimerHandle DialogueTimerHandle;



};
