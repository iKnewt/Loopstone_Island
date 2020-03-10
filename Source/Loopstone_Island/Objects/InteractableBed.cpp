// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBed.h"
#include "Loopstone_IslandGameState.h"

void AInteractableBed::Interact()
{
	// todo call something within gamestate instead
	dynamic_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState())->GoToBed();
	// UGameplayStatics::OpenLevel(this, "Fullday");
}
