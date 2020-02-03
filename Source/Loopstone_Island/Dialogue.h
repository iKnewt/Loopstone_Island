// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraph.h"
#include "Dialogue.generated.h"



/**
 * 
 */
UCLASS(Blueprintable)
class LOOPSTONE_ISLAND_API UDialogue : public UGenericGraph
{
	GENERATED_BODY()
public:
	UDialogue();

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
		FLinearColor LeftDialogueBgColor;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
		FLinearColor RightDialogueBgColor;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
		void PrintAllDialogue();
	
};
