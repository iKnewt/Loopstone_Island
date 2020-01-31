// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraphEdge.h"
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
	FText Selection;
};
