// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopstoneMachine.h"
#include "Loopstone_IslandGameState.h"
#include "Condition.h"
#include "TimerManager.h"
#include "Components/AudioComponent.h"

ALoopstoneMachine::ALoopstoneMachine()
{
	// PrimaryActorTick.bCanEverTick = true;
}

void ALoopstoneMachine::BeginPlay()
{
	Super::BeginPlay();
	this->Sound->Stop();
	ALoopstone_IslandGameState* GameState = Cast<ALoopstone_IslandGameState>(GetWorld()->GetGameState());
	if (IsValid(GameState))
	{
		GameState->Machine = this;

		FRotator Rotator;
		FVector Location;

		//todo make all of this more dynamic
		if(GameState->bCollectedLoopstones[static_cast<int>(EStory::Detective)])
		{
			// spawn in room
			Rotator = FRotator(0, 50, 0);
			Location = FVector(-3975, 480, 392);

			// display loopstones
			// hide all loopstones
			for(int i = 1; i < GameState->bCollectedLoopstones.Num(); i++)
			{
				if (GameState->bCollectedLoopstones[i])
				{
					DisplayLoopstone(static_cast<EStory>(i));
				}
			}			
		}
		else
		{
			// spawn in lighthouse
			Rotator = FRotator(0, -160, 0);
			Location = FVector(-11150.0, -2410.0, 3280.0);
			// shows all loopstones
			DisplayLoopstone(EStory::Detective);
			PlayLoopstoneSound();
		}		
		SetActorTransform(FTransform(Rotator, Location));


	}
	// FTimerHandle timer;
	// FTimerDelegate delegate;
	// GetWorldTimerManager().SetTimer(timer, this, &ALoopstoneMachine::CheckTutorialSettings, 0.5f, true);

	// if (!GameState->bEventHasBeenTriggered[static_cast<int32>(EEventType::TutorialCompleted)])
	// {
	// 	PlayLoopstoneSound();
	// }
	// else { this->SetActorTransform(FTransform(FRotator(0, 0, -40), FVector(-3975, 480, 392), FVector(3))); }
	//
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
						// PlayLoopstoneSound();
					// this->Destroy();
					// this->Sound->Stop();
					}
		}
	}
}

void ALoopstoneMachine::Interact()
{
	this->Sound->Stop();
	// sets location to room
	// todo make this more dynamic
	this->SetActorTransform(FTransform(FRotator(0,50, 0), FVector(-3975,480,392), FVector(1)));
	DisplayLoopstone(EStory::Detective, true);
}
