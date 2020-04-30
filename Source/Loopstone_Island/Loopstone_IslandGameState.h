// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Characters/BaseIslanderCharacter.h"
#include "GameStateEnums.h"
#include "Loopstone_IslandGameState.generated.h"


/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API ALoopstone_IslandGameState : public AGameStateBase
{
	GENERATED_BODY()

	void BeginPlay() override;

public:

	class ALoopstoneMachine* Machine;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite)
	// bool bUsingController = false;
	bool bTeleportAtTheEndOfConvo = false;

	float TimeLastDialogueClosed = 0;
	float SecondsBeforeYouCanTalkToIslanderAgain = 1;

	// BP of loopstone machine which is spawned when waking up
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALoopstoneMachine> LoopstoneMachineBP;

	// Current place in day and story
	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	ETimeOfDay CurrentTimeOfDay = ETimeOfDay::Morning;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Current Conditions")
	EStory CurrentStory = EStory::None;

	// Currently used condition lists
	UPROPERTY()
	TArray<bool> bEventHasBeenTriggered;
	TArray<bool> bTopicHasBeenRevealed;
	TArray<bool> bInventoryItemsCollected;

	UPROPERTY()
	TArray<class AStoryDecor*> StoryDecorActors;

	// Connected to dialogue
	UPROPERTY()
	ABaseIslanderCharacter* CurrentIslander = nullptr;
	UPROPERTY()
	class UDialogue* CurrentDialogue = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void TeleportDoctor(ABaseIslanderCharacter* Doc);
	UFUNCTION()
	void TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction = true);


	// Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<class UDialogueWidget> BP_DialogueWidget;
	class UDialogueWidget* DialogueWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<class UInventoryWidget> BP_InventoryWidget;
	class UInventoryWidget* InventoryWidget = nullptr;
	UFUNCTION()
	void EditInventoryItem(EInventoryItem Item, bool TrueToAddFalseToRemove);

	UFUNCTION()
	void SetAllItemsInBoolArray(TArray<bool> ArrayToChange, bool ValueToSet);

	int CarrotCount = 0;

	// Other
	class ASunSky* SunSky = nullptr;

	class APlayerCharacter* Player = nullptr;

	class AIslanderTargetPointController* TargetPointController = nullptr;

	TArray<class AIslandSound*> MusicActors;


	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	FString PlayerName;
	// size reflects number of possible loopstones, 0 is the actual loopstone machine
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<bool> bCollectedLoopstones;

	float PlayTimeSeconds = 0;


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

	UFUNCTION(BlueprintCallable)
	void StopAllMusic();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GoToBed();

	UFUNCTION(BlueprintCallable)
	bool CollectedAllLoopstones();
	UFUNCTION(BlueprintCallable)
	float GetSecondsPlayed();


	// testing moving condition checking here

	bool ConditionsMet(TMap<ETopic, bool> TopicBoolsConditions,
	                   TMap<EEventType, bool> EventBoolsConditions,
	                   TMap<EInventoryItem, bool> IventoryBoolsConditions = TMap<EInventoryItem, bool>(),
	                   ETimeOfDay TimeOfDayCondition = ETimeOfDay::None,
	                   EStory ActiveStoryCondition = EStory::None);

	void ChangeConditions(TMap<ETopic, bool> TopicBoolsToChange,
	                      TMap<EEventType, bool> EventBoolsToChange,
	                      TMap<EInventoryItem, bool> IventoryBoolsChange,
	                      ETimeOfDay TimeOfDayChange = ETimeOfDay::None,
	                      EStory ActiveStoryChange = EStory::None);
};

inline void ALoopstone_IslandGameState::SetAllItemsInBoolArray(TArray<bool> ArrayToChange, bool ValueToSet)
{
	for (auto Bool : ArrayToChange)
	{
		Bool = ValueToSet;
	}
}
