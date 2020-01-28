// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "BaseIslanderCharacter.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include  "Loopstone_IslandGameModeBase.h"

#include "DialogueSystem.generated.h"


/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API UDialogueSystem : public UObject
{
	GENERATED_BODY()

public:
	UDialogueSystem();
	~UDialogueSystem();
};
