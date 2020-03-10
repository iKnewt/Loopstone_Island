// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractableObjectBase.h"
#include "Kismet/GameplayStatics.h"
#include "InteractableBed.generated.h"

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API AInteractableBed : public AInteractableObjectBase
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void Interact() override;
};
