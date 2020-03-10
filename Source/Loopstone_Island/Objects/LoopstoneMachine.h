// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractableObjectBase.h"
#include "LoopstoneMachine.generated.h"

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API ALoopstoneMachine : public AInteractableObjectBase
{
	GENERATED_BODY()
public:
		ALoopstoneMachine();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		UChildActorComponent* LoopstoneOne = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UChildActorComponent* LoopstoneTwo = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UChildActorComponent* LoopstoneThree = nullptr;
	
	
	
};
