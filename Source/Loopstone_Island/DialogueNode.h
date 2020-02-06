// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraphNode.h"
#include "Loopstone_IslandGameModeBase.h"
#include "DialogueNode.generated.h"


UENUM(BlueprintType)
enum class EDialoguerPosition : uint8
{
	Left,
	Right
};

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API UDialogueNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UDialogueNode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
	FText DialogueText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
	EDialoguerPosition DialoguerPosition;


	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	// 	ETimeOfDay TimeOfDay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	TMap<EEventType, bool> EventBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	TMap<int, bool> VisitedNodesCondition;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	bool bChangesTimeOfDay = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	ETimeOfDay NewTimeOfDay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TMap<EEventType, bool> EventBoolsToChange;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Expression")
	EEyeExpression RightEyeExpression = EEyeExpression::Eye_Blinking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Expression")
	EEyeExpression LeftEyeExpression = EEyeExpression::Eye_Blinking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Expression")
	EMouthExpression MouthExpression = EMouthExpression::Mouth_Talk;

	UFUNCTION()
	void PrintSelfAndChildren();

	bool bHasBeenVisited = false;


#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;

	virtual void SetNodeTitle(const FText& NewTitle) override;

	virtual FLinearColor GetBackgroundColor() const override;
#endif
};
