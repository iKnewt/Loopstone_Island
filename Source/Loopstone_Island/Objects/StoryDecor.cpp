// Fill out your copyright notice in the Description page of Project Settings.

#include "StoryDecor.h"

#include "Systems/Loopstone_IslandGameState.h"

// Sets default values
AStoryDecor::AStoryDecor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AStoryDecor::UnhideIfConditionsMet(ETimeOfDay TimeOfDay, EStory Story)
{

	if (TimeOfDay == TimeOfDayCondition && Story == ActiveStoryCondition)
	{
		this->SetActorHiddenInGame(false);
	}
}

// Called when the game starts or when spawned
void AStoryDecor::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorHiddenInGame(true);
	
	ALoopstone_IslandGameState* GameState = Cast<ALoopstone_IslandGameState>(GetWorld()->GetGameState());
	if(GameState)
	{
		GameState->StoryDecorActors.Add(this);
	}	
}

// Called every frame
void AStoryDecor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

