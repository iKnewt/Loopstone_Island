// Fill out your copyright notice in the Description page of Project Settings.


#include "LoopstoneMachine.h"
#include "Loopstone_IslandGameState.h"

ALoopstoneMachine::ALoopstoneMachine()
{
	LoopstoneOne = CreateDefaultSubobject<UActorComponent>(TEXT("Loopstone 1"));
	LoopstoneTwo = CreateDefaultSubobject<UActorComponent>(TEXT("Loopstone 2"));
	LoopstoneThree = CreateDefaultSubobject<UActorComponent>(TEXT("Loopstone 3"));
}

void ALoopstoneMachine::BeginPlay()
{
	ALoopstone_IslandGameState* GameState = Cast<ALoopstone_IslandGameState>(GetWorld()->GetGameState());
	if (IsValid(GameState))
	{
		GameState->Machine = this;
	}
}
