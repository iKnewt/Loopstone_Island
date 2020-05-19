// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStateEnums.h"
#include "IslanderTargetPointController.generated.h"


UCLASS()
class LOOPSTONE_ISLAND_API AIslanderTargetPointController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIslanderTargetPointController();

	UFUNCTION(BlueprintCallable)
	void MoveIslandersToPosition(ETimeOfDay NewTimeOfDay, EStory CurrentStory);
	TArray<class ABaseIslanderCharacter*> Islanders;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetupIslandersArray();

	void SetupIslandPositions();
	// Every IslanderTargetPoint on the map.
	// Sorted so that we do not have to do a for loop each time
	TArray<TArray<TArray<class AIslanderTargetPoint*>>> Points;
};
