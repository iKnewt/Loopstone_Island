// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "Loopstone_IslandGameState.h"
#include "GameStateEnums.h"
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

	//~=============================================================================
	// Conditions	
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

	//~=============================================================================
	// Conditions to Change if Conditions are met	
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

	//If currently visualizing its interactivity
	bool bVisualizingInteraction = false;

protected:
	//~=============================================================================
	// Components		
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh = nullptr;
	//The sound it makes whenever you interact with the object
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAudioComponent* Sound;

	//~=============================================================================
	// Materials	
	void CreateDynamicMaterial();
	UMaterialInstanceDynamic* Material = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InventoryIcon = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
