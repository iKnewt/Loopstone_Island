// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Characters/BaseIslanderCharacter.h"
#include "GameStateEnums.h"
#include "Objects/InteractableBook.h"
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

	//~=============================================================================
	// Conditions

	// Current place in day and story
	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	ETimeOfDay CurrentTimeOfDay = ETimeOfDay::Morning;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Current Conditions")
	EStory CurrentStory = EStory::None;

	TArray<bool> bEventHasBeenTriggered;

	TArray<bool> bTopicHasBeenRevealed;

	TArray<bool> bInventoryItemsCollected;

	UFUNCTION(BlueprintCallable)
	void ChangeTimeOfDay(ETimeOfDay NewTimeOfDay);

	void ChangeStory(EStory NewStory);

	bool AreConditionsMet(TMap<ETopic, bool> TopicBoolsConditions,
	                      TMap<EEventType, bool> EventBoolsConditions,
	                      TMap<EInventoryItem, bool> IventoryBoolsConditions = TMap<EInventoryItem, bool>(),
	                      ETimeOfDay TimeOfDayCondition = ETimeOfDay::None,
	                      EStory ActiveStoryCondition = EStory::None);

	void ChangeConditions(TMap<ETopic, bool> TopicBoolsToChange,
	                      TMap<EEventType, bool> EventBoolsToChange,
	                      TMap<EInventoryItem, bool> IventoryBoolsChange,
	                      ETimeOfDay TimeOfDayChange = ETimeOfDay::None,
	                      EStory ActiveStoryChange = EStory::None);

	UFUNCTION(BlueprintCallable)
	bool HasCollectedAllLoopstones();

	UFUNCTION(BlueprintCallable)
	void CollectLoopstone(EStory StoryOwningLoopstone);

	//~=============================================================================
	// Objects on the map

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALoopstoneMachine> LoopstoneMachineBP;

	class ALoopstoneMachine* Machine;

	class ASunSky* SunSky = nullptr;

	class APlayerCharacter* Player = nullptr;

	class AIslanderTargetPointController* TargetPointController = nullptr;

	TArray<class AIslandSound*> MusicActors;

	TArray<class AStoryDecor*> StoryDecorActors;

	float PlayTimeSeconds = 0;

	float TimeLastDialogueClosed = 0;

	float SecondsBeforeYouCanTalkToIslanderAgain = 1;

	//~=============================================================================
	// Dialogue

	UPROPERTY()
	ABaseIslanderCharacter* CurrentIslander = nullptr;

	UPROPERTY()
	class UDialogue* CurrentDialogue = nullptr;

	bool bTeleportAtTheEndOfConvo = false;
	UFUNCTION(BlueprintImplementableEvent)

	void TeleportDoctor(ABaseIslanderCharacter* Doc);
	UFUNCTION()

	void TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction = true);

	bool StartDialogue(ABaseIslanderCharacter* Islander);

	bool StartDialogue(AInteractableBook* Book);

	void CloseDialogue();

	bool UpdateDialogueBasedOnResponse(int ResponseID);

	//~=============================================================================
	// Widgets

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<class UDialogueWidget> BP_DialogueWidget;

	class UDialogueWidget* DialogueWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<class UInventoryWidget> BP_InventoryWidget;

	class UInventoryWidget* InventoryWidget = nullptr;

	// inventory stuff
	int CarrotCount = 0;

	UFUNCTION()
	void EditInventoryItem(EInventoryItem Item, bool TrueToAddFalseToRemove);


	//~=============================================================================
	// Saving

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	FString PlayerName;
	// size reflects number of possible loopstones, 0 is the actual loopstone machine
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<bool> bCollectedLoopstones;

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	//~=============================================================================
// Other

	void InteractWithObject(class AInteractableObjectBase* InteractableObject);

	UFUNCTION(BlueprintCallable)
	void StopAllMusic();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void GoToBed();

	UFUNCTION(BlueprintCallable)
	float GetSecondsPlayed();

	UFUNCTION()
	void SetAllItemsInBoolArray(TArray<bool> ArrayToChange, bool ValueToSet);
};
