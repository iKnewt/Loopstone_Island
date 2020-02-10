// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseIslanderCharacter.h"
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
	UPROPERTY()
	TArray<bool> bEventHasBeenTriggered;
	TArray<bool> bTopicHasBeenRevealed;

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
	
	class UDialogueWidget* DialogueWidget = nullptr;

	class ASunSky* SunSky = nullptr;

	class APlayerCharacter* Player = nullptr;

	/**
* Opens Dialogue
*/
	bool InteractWithObject(class AInteractableObjectBase* InteractableObject);
	
	bool StartDialogue(ABaseIslanderCharacter* Islander);

	void CloseDialogue();

	bool UpdateDialogueBasedOnResponse(int ResponseID);

	void ChangeTimeOfDay(ETimeOfDay NewTimeOfDay);

	void ChangeStory(EStory NewStory);
};
