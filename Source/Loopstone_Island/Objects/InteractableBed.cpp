// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBed.h"
#include "Systems/Loopstone_IslandGameState.h"

void AInteractableBed::Interact()
{
	dynamic_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState())->GoToBed();
}
