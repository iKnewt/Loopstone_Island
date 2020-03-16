// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Characters/BaseIslanderCharacter.h"
#include "Condition.h"
#include "Loopstone_IslandGameState.generated.h"


USTRUCT()
struct FCurrentConditions
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<bool> bConditions;
};

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API ALoopstone_IslandGameState : public AGameStateBase
{
	GENERATED_BODY()

	void BeginPlay() override;
	void EditInventory(bool NewBoolValue);

public:
	UPROPERTY()
	TArray<bool> bEventHasBeenTriggered;
	TArray<bool> bTopicHasBeenRevealed;

	TArray<FCurrentConditions> bConditionLists;
	
	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	ETimeOfDay CurrentTimeOfDay = ETimeOfDay::Morning;

	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	EStory CurrentStory = EStory::None;

	UPROPERTY()
	ABaseIslanderCharacter* CurrentIslander = nullptr;

	UPROPERTY()
	class UDialogue* CurrentDialogue = nullptr;

	UFUNCTION()
	bool TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction = true);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<class UDialogueWidget> BP_DialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TArray<USoundBase*> Music;

	class UDialogueWidget* DialogueWidget = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<class UInventoryWidget> BP_InventoryWidget;

	class UInventoryWidget* InventoryWidget = nullptr;

	class ASunSky* SunSky = nullptr;

	class APlayerCharacter* Player = nullptr;

	class AIslanderTargetPointController* TargetPointController = nullptr;

	TArray<class AIslandSound*> MusicActors;

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
		FString PlayerName;

	// size reflects number of possible loopstones, 0 is the actual loopstone machine
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
		TArray<bool> bCollectedLoopstones;

	class ALoopstoneMachine* Machine = nullptr;

	/**
* Opens Dialogue
*/
	bool InteractWithObject(class AInteractableObjectBase* InteractableObject);

	bool StartDialogue(ABaseIslanderCharacter* Islander);

	void CloseDialogue();

	bool UpdateDialogueBasedOnResponse(int ResponseID);

	UFUNCTION(BlueprintCallable)
	void ChangeTimeOfDay(ETimeOfDay NewTimeOfDay);

	void ChangeStory(EStory NewStory);

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintCallable)
	void CollectLoopstone(EStory StoryOwningLoopstone);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GoToBed();
};
