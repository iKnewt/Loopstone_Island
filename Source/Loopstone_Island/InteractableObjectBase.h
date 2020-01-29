// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObjectBase.generated.h"



UCLASS()
class LOOPSTONE_ISLAND_API AInteractableObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObjectBase();

	virtual void Interact(){}
	virtual void VisualizeInteraction(bool bActivate){}
	bool bVisualizingInteraction = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
