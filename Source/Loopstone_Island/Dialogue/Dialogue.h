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
	TArray<class UDialogueEdge*> CurrentAvailableEdges;
	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	class ABaseIslanderCharacter* CurrentIslander = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	class UDialogueNode* LastMenuNode = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Current Conditions")
	class UDialogueNode* LastConditionNode = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TArray<bool> Conditions;
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TMap<FName, bool> NamedConditions;
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ResetDialogue();
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void UpdateCurrentOptions(class ALoopstone_IslandGameState* GameState);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	TArray<FString> GetCurrentOptions(ALoopstone_IslandGameState* GameState);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool UpdateCurrentNode(int ResponseID, class ALoopstone_IslandGameState* GameState);

	bool CurrentDialogueNodeConditionsMet(ALoopstone_IslandGameState* GameState);
};
