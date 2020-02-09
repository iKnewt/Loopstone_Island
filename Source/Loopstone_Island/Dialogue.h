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

	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	class UDialogueNode* CurrentDialogueNode = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	TArray<class UDialogueEdge*> CurrentAvailableOptions;

	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	class ABaseIslanderCharacter* CurrentIslander = nullptr;

	// UPROPERTY()
	// class ALoopstone_IslandGameState* GameState = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FLinearColor Color1;
	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FLinearColor Color2;
	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FLinearColor Color3;
	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FLinearColor Color4;
	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FLinearColor Color5;
	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FLinearColor Color6;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TArray<bool> Conditions;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TMap<FName, bool> NamedConditions;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void PrintAllDialogue();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool UpdateCurrentNode(int ResponseID, class ALoopstone_IslandGameState* GameState);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void UpdateEventLibaryBasedOnCurrentNode(ALoopstone_IslandGameState* GameState);
};
