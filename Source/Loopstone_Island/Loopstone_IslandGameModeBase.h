// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Dialogue.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "BaseIslanderCharacter.h"
#include "Loopstone_IslandGameModeBase.generated.h"

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
UCLASS(Blueprintable)
class LOOPSTONE_ISLAND_API ALoopstone_IslandGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALoopstone_IslandGameModeBase();

	void BeginPlay() override;

	UPROPERTY()
	TArray<bool> bEventHasBeenTriggered;

	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	ETimeOfDay CurrentTimeOfDay = ETimeOfDay::Morning;

	UPROPERTY(EditDefaultsOnly, Category = "Current Conditions")
	EStory CurrentStory = EStory::None;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDialogue* GameDialogue;

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

	UPROPERTY()
	ABaseIslanderCharacter* CurrentIslander = nullptr;

	UPROPERTY()
	class UDialogue* CurrentDialogueGraph = nullptr;
	bool UpdateDialogueBasedOnResponse(int ResponseID);
};
