// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameStateEnums.h"
#include "IslanderTargetPoint.generated.h"


/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API AIslanderTargetPoint : public ATargetPoint
{
	GENERATED_BODY()
public:

	//~=============================================================================
	// Conditions
	// Used to check when the specific islander gets put on this specic
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETimeOfDay TimeOfDay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EIslanderType Islander;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EStory Story;
	
	
	
	
};
