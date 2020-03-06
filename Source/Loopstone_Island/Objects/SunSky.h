// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Loopstone_IslandGameState.h"
#include "SunSky.generated.h"

UCLASS()
class LOOPSTONE_ISLAND_API ASunSky : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASunSky();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeTimeOfDay(ETimeOfDay TimeOfDay);
};
