// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStateEnums.h"
#include "StoryDecor.generated.h"

UCLASS()
class LOOPSTONE_ISLAND_API AStoryDecor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStoryDecor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	ETimeOfDay TimeOfDayCondition = ETimeOfDay::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
	EStory ActiveStoryCondition = EStory::None;

	void UnhideIfConditionsMet(ETimeOfDay TimeOfDay, EStory Story);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
