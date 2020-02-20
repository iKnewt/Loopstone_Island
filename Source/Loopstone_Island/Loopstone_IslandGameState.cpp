// Fill out your copyright notice in the Description page of Project Settings.


#include "Loopstone_IslandGameState.h"
#include "DialogueWidget.h"
#include "Dialogue.h"
#include "DialogueEdge.h"
#include "DialogueNode.h"
#include "SunSky.h"
#include "InteractableObjectBase.h"
#include "InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "IslanderTargetPointController.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetBlueprintLibrary.h"

void ALoopstone_IslandGameState::BeginPlay()
{
	Super::BeginPlay();

	ChangeTimeOfDay(ETimeOfDay::Morning);

	bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bEventHasBeenTriggered contains:  %i"), bEventHasBeenTriggered.Num());

	bTopicHasBeenRevealed.SetNum(static_cast<int>(ETopic::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bTopicHasBeenRevealed contains:  %i"), bTopicHasBeenRevealed.Num());


	if (BP_DialogueWidget)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld()->GetFirstPlayerController(), BP_DialogueWidget);
		DialogueWidget->AddToViewport();
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (!DialogueWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("DIALOGUE WIDGET NOT CREATED"));
	}

	if (BP_InventoryWidget)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld()->GetFirstPlayerController(), BP_InventoryWidget);
		InventoryWidget->AddToViewport();
	}
	if (!InventoryWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("INVENTORY WIDGET NOT CREATED"));
	}

	//Spawning target point controllers
	TargetPointController = Cast<AIslanderTargetPointController>(GetWorld()->SpawnActor(AIslanderTargetPointController::StaticClass()));
}

bool ALoopstone_IslandGameState::TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction)
{
	bEventHasBeenTriggered[static_cast<int>(EventType)] = NewBoolValue;

	UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(EventType),
	       (NewBoolValue ? TEXT("true") : TEXT("false")));

	if(!InventoryWidget)
	{
		return true;
	}

	if (RunFunction)
	{
		switch (EventType)
		{
		case EEventType::HasTape:
		{
			InventoryWidget->EditInventoryItem(EItem::Tape, NewBoolValue);
			break;
		}
		case EEventType::HasRope:
		{
			InventoryWidget->EditInventoryItem(EItem::Rope, NewBoolValue);
			break;
		}
		case EEventType::HasKnife:
		{
			InventoryWidget->EditInventoryItem(EItem::Knife, NewBoolValue);
			break;
		}
		case EEventType::None:
			break;
		default:;
		}
	}

	return true;
}

bool ALoopstone_IslandGameState::InteractWithObject(AInteractableObjectBase* InteractableObject)
{
	// CHECK CONDITIONS

	// todo make better implementation of condition checking
	for (auto Element : InteractableObject->EventBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != this->bEventHasBeenTriggered[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}
	for (auto Element : InteractableObject->TopicBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != this->bTopicHasBeenRevealed[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}

	if (InteractableObject->TimeOfDayCondition != ETimeOfDay::None &&
		InteractableObject->TimeOfDayCondition != this->CurrentTimeOfDay)
	{
		return false;
	}
	if (InteractableObject->ActiveStoryCondition != EStory::None &&
		InteractableObject->ActiveStoryCondition != this->CurrentStory)
	{
		return false;
	}


	// if all conditions pass

	// do any local changes to the object
	InteractableObject->Interact();

	// CHECK GLOBAL EVENT TRIGGER
	// todo make better implementation for event trigger
	for (auto Element : InteractableObject->EventBoolsToChange)
	{
		this->TriggerEvent(Element.Key, Element.Value);
	}
	for (auto Element2 : InteractableObject->TopicBoolsToChange)
	{
		this->bTopicHasBeenRevealed[static_cast<int>(Element2.Key)] = Element2.Value;
	}

	if (InteractableObject->TimeOfDayChange != ETimeOfDay::None)
	{
		this->ChangeTimeOfDay(InteractableObject->TimeOfDayChange);
	}
	if (InteractableObject->ActiveStoryChange != EStory::None)
	{
		this->ChangeStory(InteractableObject->ActiveStoryChange);
	}
	return true;
}

bool ALoopstone_IslandGameState::StartDialogue(ABaseIslanderCharacter* Islander)
{
	if (!Islander || !DialogueWidget)
	{
		return false;
	}

	if (Islander->Dialogue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue started with %s"), *Islander->Name);

		CurrentIslander = Islander;
		CurrentDialogue = Islander->Dialogue;

		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(Islander, 0.5f);
		
		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), DialogueWidget);

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		CurrentDialogue->CurrentDialogueNode = nullptr;

		DialogueWidget->SetSpeakerName(Islander->Name);
		DialogueWidget->SetRichStyleText(Islander->RichTextStyles);
		UpdateDialogueBasedOnResponse(0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no dialogue"), *Islander->Name);
	}
	return true;
}

void ALoopstone_IslandGameState::CloseDialogue()
{
	if (DialogueWidget)
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), DialogueWidget);
		CurrentIslander = nullptr;
		CurrentDialogue->CurrentDialogueNode = nullptr;
		CurrentDialogue = nullptr;

		DialogueWidget->Dialogue_Text->SetText(FText::FromString(" "));

		// swap camera
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(GetWorld()->GetFirstPlayerController()->GetPawn(), 0.5f);
		
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
	}
}

bool ALoopstone_IslandGameState::UpdateDialogueBasedOnResponse(int ResponseID)
{
	if (!CurrentDialogue->UpdateCurrentNode(ResponseID, this))
	{
		CloseDialogue();
		return false;
	}
	// todo move this check into dialogue system somehow

	while(CurrentDialogue->CurrentDialogueNode->NodeExits == ENodeExits::Condition)
	{
		if (!CurrentDialogue->UpdateCurrentNode(ResponseID, this))
		{
			CloseDialogue();
			return false;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("trying to update event library"));
	CurrentDialogue->UpdateEventLibaryBasedOnCurrentNode(this);

	FString DialogueText = "Oh hello....";

	// update the dialogue widget
	DialogueText = CurrentDialogue->CurrentDialogueNode->DialogueText.ToString();

	// Change facial expression on islander
	CurrentIslander->ChangeMouthExpression(CurrentDialogue->CurrentDialogueNode->MouthExpression);
	CurrentIslander->ChangeEyeExpression(CurrentDialogue->CurrentDialogueNode->RightEyeExpression, CurrentDialogue->CurrentDialogueNode->LeftEyeExpression);
	// Change animation??

	DialogueWidget->SetDialogueWithOptions(0.01f, DialogueText, CurrentDialogue->GetCurrentOptions(this));

	return true;
}

void ALoopstone_IslandGameState::ChangeTimeOfDay(ETimeOfDay NewTimeOfDay)
{
	CurrentTimeOfDay = NewTimeOfDay;
	if (SunSky)
	{
		SunSky->ChangeTimeOfDay(NewTimeOfDay);
		
		if(Music.Num() > static_cast<int>(NewTimeOfDay))
		{
			if(Music[static_cast<int>(NewTimeOfDay)])
			{
				// UGameplayStatics::PlaySound2D(GetWorld(), Music[static_cast<int>(NewTimeOfDay)]);
			}
		}
		if(IsValid(TargetPointController))
		{
			TargetPointController->MoveIslandersToPosition(NewTimeOfDay);
		}
	}
}

void ALoopstone_IslandGameState::ChangeStory(EStory NewStory)
{
	CurrentStory = NewStory;

	// Do functionality if any.
}
