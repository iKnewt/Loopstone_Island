// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraphNode.h"
#include "Loopstone_IslandGameState.h"
#include "Condition.h"
#include "DialogueNode.generated.h"

UENUM(BlueprintType)
enum class ENodeExits : uint8
{
	NoOptions,
	OptionsWithExit,
	ReturnToLastOptionsWithExit,
	Options,
	Condition,
	ReturnToRoot,
	None
};

UENUM()
enum class EPlantType
{
	Flower,
	Food,
	Poison
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

	UPROPERTY(EditDefaultsOnly)
		bool bHasFlowers = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
	FText DialogueText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue")
	ENodeExits NodeExits = ENodeExits::NoOptions;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	TMap<EEventType, bool> EventBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	TMap<ETopic, bool> TopicBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	ETimeOfDay TimeOfDayCondition = ETimeOfDay::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	EStory ActiveStoryCondition = EStory::None;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TMap<ETopic, bool> TopicBoolsToChange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TMap<EEventType, bool> EventBoolsToChange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	ETimeOfDay TimeOfDayChange = ETimeOfDay::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	EStory ActiveStoryChange = EStory::None;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Expression")
	EEyeExpression RightEyeExpression = EEyeExpression::Eye_Blinking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Expression")
	EEyeExpression LeftEyeExpression = EEyeExpression::Eye_Blinking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Expression")
	EMouthExpression MouthExpression = EMouthExpression::Mouth_Smile;


	// Origin within SourceImage, prior to atlasing
	UPROPERTY(Category = Sprite, EditAnywhere, AdvancedDisplay, meta = (EditCondition = "bTrimmedInSourceImage"))
		FVector2D OriginInSourceImageBeforeTrimming;

	// This texture is trimmed, consider the values above
	UPROPERTY(Category = Sprite, EditAnywhere, AdvancedDisplay)
		bool bTrimmedInSourceImage = true;
	


	UFUNCTION()
	void PrintSelfAndChildren();

	UFUNCTION()
	bool ConditionsMet(class ALoopstone_IslandGameState* GameState);

	bool bHasBeenVisited = false;


#if WITH_EDITOR
	
	virtual FText GetNodeTitle() const override;

	virtual void SetNodeTitle(const FText& NewTitle) override;

	virtual FLinearColor GetBackgroundColor() const override;

	virtual bool CanEditChange(const UProperty* InProperty) const override;

#endif
};
