// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionalTriggerBox.h"
#include "Loopstone_IslandGameState.h"

// Sets default values
AConditionalTriggerBox::AConditionalTriggerBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

 bool AConditionalTriggerBox::ConditionsMet()
{
	ALoopstone_IslandGameState* GameState = Cast<ALoopstone_IslandGameState>(GetWorld()->GetGameState());
	if (IsValid(GameState))
	{
		return GameState->AreConditionsMet(TopicBoolsConditions,
		                                EventBoolsConditions,
		                                InventoryBoolsConditions,
		                                TimeOfDayCondition,
		                                ActiveStoryCondition);
	}
	return false;
}
