// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractableObjectBase.h"
#include "Loopstone.generated.h"

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API ALoopstone : public AInteractableObjectBase
{
	GENERATED_BODY()
public:
	ALoopstone();
	void BeginPlay() override;
};
