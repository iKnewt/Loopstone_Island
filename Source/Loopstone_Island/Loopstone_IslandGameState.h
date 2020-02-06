// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseIslanderCharacter.h"
#include "Loopstone_IslandGameState.generated.h"

UENUM(BlueprintType)
enum class ETimeOfDay : uint8
{
	Morning,
	Afternoon,
	Evening,
	Night,
	None
};

UENUM(BlueprintType)
enum class EStory : uint8
{
	PartyPlanner,
	AssistantChef,
	None
};

UENUM(BlueprintType)
enum class EEventType : uint8
{
	HasRope,
	None
};

UENUM(BlueprintType)
enum class ETopic : uint8
{
	Tape,
	Rope,
	Party,
	None
};

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

	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	ETimeOfDay CurrentTimeOfDay = ETimeOfDay::Morning;

	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	EStory CurrentStory = EStory::None;

	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	int TEST = 0;

	ABaseIslanderCharacter* CurrentIslander;

	class UDialogue* CurrentDialogueGraph;

	UFUNCTION()
	bool TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction = false);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSubclassOf<class UDialogueWidget> BP_DialogueWidget;
	
	class UDialogueWidget* DialogueWidget;

	/**
* Opens Dialogue
*/
	void StartDialogue(ABaseIslanderCharacter* Islander);

	void CloseDialogue();

	bool UpdateDialogueBasedOnResponse(int ResponseID);
};
