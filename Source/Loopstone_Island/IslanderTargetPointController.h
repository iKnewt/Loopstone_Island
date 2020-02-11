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
		void MoveIslandersToPosition(ETimeOfDay NewTimeOfDay);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetupIslandersArray();

	void SetupIslandPositions();

	TArray<class ABaseIslanderCharacter*> Islanders;

	TArray<TArray<class AIslanderTargetPoint*>> Points;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
