// Fill out your copyright notice in the Description page of Project Settings.


#include "SunSky.h"
#include "Loopstone_IslandGameModeBase.h"

// Sets default values
ASunSky::ASunSky()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASunSky::BeginPlay()
{
	Super::BeginPlay();

	ALoopstone_IslandGameState* GameState = dynamic_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState());
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("CORRECT GAME STATE NOT FOUND IN SUNSKY"));
	}
	else
	{
		GameState->SunSky = this;
	}
}

// Called every frame
void ASunSky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
