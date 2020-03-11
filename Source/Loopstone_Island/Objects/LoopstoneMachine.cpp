// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopstoneMachine.h"
#include "Loopstone_IslandGameState.h"
#include "Condition.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"

ALoopstoneMachine::ALoopstoneMachine()
{
}

void ALoopstoneMachine::BeginPlay()
{
	ALoopstone_IslandGameState* GameState = Cast<ALoopstone_IslandGameState>(GetWorld()->GetGameState());
	if (IsValid(GameState))
	{
		GameState->Machine = this;
	}
	FTimerHandle timer;
	FTimerDelegate delegate;
	GetWorldTimerManager().SetTimer(timer, this, &ALoopstoneMachine::CheckTutorialSettings, 0.5f, true);
}

void ALoopstoneMachine::CheckTutorialSettings()
{
	ALoopstone_IslandGameState* GameState = Cast<ALoopstone_IslandGameState>(GetWorld()->GetGameState());
	if (IsValid(GameState))
	{
		if(GameState->bEventHasBeenTriggered.Num() > 0)
		{
					if(GameState->bEventHasBeenTriggered[static_cast<int32>(EEventType::TutorialCompleted)])
					{
					this->Destroy();
					this->Sound->Stop();
					}
		}
	}
}
