// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraph.h"
#include "EventLibrary.h"
#include "Dialogue.generated.h"

UENUM(BlueprintType)
enum class EEventType : uint8
{
	HasTape,
	None
};

UENUM(BlueprintType)
enum class ETimeOfDay : uint8
{
	Morning,
	Afternoon,
	Evening,
	Night
};

UENUM(BlueprintType)
enum class EStory : uint8
{
	PartyPlanner,
	AssistantChef,
	None
};

/**
 * 
 */
UCLASS(Blueprintable)
class LOOPSTONE_ISLAND_API UDialogue : public UGenericGraph
{
	GENERATED_BODY()
public:
	UDialogue();

	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	ETimeOfDay CurrentTimeOfDay = ETimeOfDay::Morning;

	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	EStory CurrentStory = EStory::None;

	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	class UDialogueNode* CurrentDialogueNode = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	TArray<class UDialogueEdge*> CurrentAvailableOptions;

	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	class ABaseIslanderCharacter* CurrentIslander = nullptr;


	// UPROPERTY(BlueprintReadOnly, Category = "Event Library")
	// UEventLibrary* EventLibrary;

	UPROPERTY()
		TArray<bool> bEventHasBeenTriggered;

	UFUNCTION()
		bool TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction = false);


	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FLinearColor LeftDialogueBgColor;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FLinearColor RightDialogueBgColor;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TArray<bool> Conditions;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TMap<FName, bool> NamedConditions;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void PrintAllDialogue();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void GetDialogueText();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool UpdateCurrentNode(int ResponseID);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void UpdateEventLibaryBasedOnCurrentNode();
};
