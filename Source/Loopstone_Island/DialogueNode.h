// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraphNode.h"
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

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;

	virtual void SetNodeTitle(const FText& NewTitle) override;

	virtual FLinearColor GetBackgroundColor() const override;
#endif
};
