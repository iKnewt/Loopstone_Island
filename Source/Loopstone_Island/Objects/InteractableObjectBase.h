// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Condition.h"
#include "Loopstone_IslandGameState.h"
#include "InteractableObjectBase.generated.h"


UCLASS()
class LOOPSTONE_ISLAND_API AInteractableObjectBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableObjectBase();

	// UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	virtual void Interact();

	virtual void DoNotInteract()
	{
	}

	virtual void VisualizeInteraction(bool bActivate);

	bool bVisualizingInteraction = false;


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh = nullptr;

	//The sound it makes whenever you interact with the object
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAudioComponent* Sound;

	void CreateDynamicMaterial();

	UMaterialInstanceDynamic* Material = nullptr;

	bool bGlowing = false;


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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TMap<ETopic, bool> TopicBoolsToChange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TMap<EEventType, bool> EventBoolsToChange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	TMap<EInventoryItem, bool> InventoryBoolsChange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	ETimeOfDay TimeOfDayChange = ETimeOfDay::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Event")
	EStory ActiveStoryChange = EStory::None;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
