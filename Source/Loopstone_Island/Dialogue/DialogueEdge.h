// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraphEdge.h"
#include "Systems/Loopstone_IslandGameState.h"
#include "DialogueEdge.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LOOPSTONE_ISLAND_API UDialogueEdge : public UGenericGraphEdge
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
	FString OptionText = "...";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	TMap<ETopic, bool> TopicBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	TMap<EEventType, bool> EventBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	TMap<EInventoryItem, bool> InventoryBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	ETimeOfDay TimeOfDayCondition = ETimeOfDay::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	EStory ActiveStoryCondition = EStory::None;
};
