// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Loopstone_Island_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API ULoopstone_Island_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString PlayerName;

	// size reflects number of possible loopstones, 0 is the actual loopstone machine
	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<bool> bCollectedLoopstones;

	// UPROPERTY(VisibleAnywhere, Category = Basic)
	// bool bIsUsingController;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	float PlayTimeSeconds;
};
