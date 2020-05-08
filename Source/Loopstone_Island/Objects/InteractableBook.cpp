// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBook.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Loopstone_IslandGameState.h"

AInteractableBook::AInteractableBook()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(this->GetRootComponent());

	// maybe call on begin play
	// if (Dialogue)
	// {
	// 	Dialogue->ResetDialogue();
	// }
	
}

void AInteractableBook::Interact()
{
	dynamic_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState())->StartDialogue(this);
	
	// open dialogue and stuff
	
}
