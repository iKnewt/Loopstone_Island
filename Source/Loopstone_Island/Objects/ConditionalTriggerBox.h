// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStateEnums.h"
#include "ConditionalTriggerBox.generated.h"

UCLASS()
class LOOPSTONE_ISLAND_API AConditionalTriggerBox : public AActor
{
	GENERATED_BODY()
 
public:
	// Sets default values for this actor's properties
	AConditionalTriggerBox();
	//~=============================================================================
	// Conditions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	TMap<ETopic, bool> TopicBoolsConditions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	TMap<EEventType, bool> EventBoolsConditions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	TMap<EInventoryItem, bool> InventoryBoolsConditions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	ETimeOfDay TimeOfDayCondition = ETimeOfDay::None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	EStory ActiveStoryCondition = EStory::None;

	UFUNCTION(BlueprintCallable)
		bool ConditionsMet();
};
