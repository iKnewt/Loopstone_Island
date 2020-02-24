// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStateEnums.h"
#include "InteractableObjectBase.generated.h"


UCLASS()
class LOOPSTONE_ISLAND_API AInteractableObjectBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableObjectBase()
	{
	}

	// UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	virtual void Interact();

	virtual void VisualizeInteraction(bool bActivate)
	{
	}

	bool bVisualizingInteraction = false;


	// UPROPERTY(VisibleAnywhere)
	// 	UStaticMeshComponent* ObjectMesh = nullptr;
	//
	// void CreateDynamicMaterial();
	//
	// UMaterialInstanceDynamic* Material = nullptr;
	//
	// bool bGlowing = false;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	TMap<EEventType, bool> EventBoolsConditions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	TMap<ETopic, bool> TopicBoolsConditions;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	ETimeOfDay TimeOfDayCondition = ETimeOfDay::None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Condition")
	EStory ActiveStoryCondition = EStory::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event")
	TMap<ETopic, bool> TopicBoolsToChange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event")
	TMap<EEventType, bool> EventBoolsToChange;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event")
	ETimeOfDay TimeOfDayChange = ETimeOfDay::None;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Event")
	EStory ActiveStoryChange = EStory::None;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
