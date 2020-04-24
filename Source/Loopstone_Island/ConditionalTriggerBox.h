// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStateEnums.h"
#include "ConditionalTriggerBox.generated.h"

UCLASS()
class LOOPSTONE_ISLAND_API AConditionalTriggerBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConditionalTriggerBox();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
		TMap<ETopic, bool> TopicBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
		TMap<EEventType, bool> EventBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
		TMap<EInventoryItem, bool> InventoryBoolsConditions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
		ETimeOfDay TimeOfDayCondition = ETimeOfDay::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Condition")
		EStory ActiveStoryCondition = EStory::None;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
