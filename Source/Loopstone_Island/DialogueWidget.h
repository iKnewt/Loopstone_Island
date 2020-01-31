// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
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
		FString DialogueTest = "helo";

	void SetDialogue(FString Dialogue);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void SetCurrentDialogueText();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void RevealOptions();

private:
	void AddLetterToDialogue();



};
