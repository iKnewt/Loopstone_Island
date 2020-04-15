// Fill out your copyright notice in the Description page of Project Settings.


#include "Loopstone_IslandGameState.h"
#include "GUI/DialogueWidget.h"
#include "Dialogue/Dialogue.h"
#include "Dialogue/DialogueNode.h"
#include "Objects/SunSky.h"
#include "Objects/InteractableObjectBase.h"
#include "GUI/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Objects/IslanderTargetPointController.h"
#include "WidgetBlueprintLibrary.h"
#include "Objects/IslandSound.h"
#include "Loopstone_Island_SaveGame.h"
#include "Objects/LoopstoneMachine.h"
#include "Button.h"

void ALoopstone_IslandGameState::BeginPlay()
{
	Super::BeginPlay();

	TimeLastDialogueClosed = UGameplayStatics::GetTimeSeconds(GetWorld());

	UE_LOG(LogTemp, Warning, TEXT("Besinning play"));

	ChangeTimeOfDay(ETimeOfDay::Morning);

	UE_LOG(LogTemp, Warning, TEXT("morning started"));

	bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bEventHasBeenTriggered contains:  %i"), bEventHasBeenTriggered.Num());

	bTopicHasBeenRevealed.SetNum(static_cast<int>(ETopic::None) + 1);
	UE_LOG(LogTemp, Warning, TEXT("bTopicHasBeenRevealed contains:  %i"), bTopicHasBeenRevealed.Num());

	bCollectedLoopstones.SetNum(static_cast<int>(EStory::None));


	bConditionLists.SetNum(static_cast<int>(EConditionListType::None));
	bConditionLists[static_cast<int>(EConditionListType::Event)].bConditions.SetNum(
		static_cast<int>(EEventType::None) + 1);
	bConditionLists[static_cast<int>(EConditionListType::Topic)].bConditions.SetNum(static_cast<int>(ETopic::None) + 1);


	if (BP_DialogueWidget)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld()->GetFirstPlayerController(), BP_DialogueWidget);
		DialogueWidget->AddToViewport();
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
		DialogueWidget->GameState = this;
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
	TargetPointController = Cast<AIslanderTargetPointController>(
		GetWorld()->SpawnActor(AIslanderTargetPointController::StaticClass()));

	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

	LoadGame();


	// LOOPSTONE MACHINE SPAWN TEST
	if (LoopstoneMachineBP)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		Machine = GetWorld()->SpawnActor<ALoopstoneMachine>(LoopstoneMachineBP, SpawnParameters);
	}


	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController());
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
}

void ALoopstone_IslandGameState::SaveGame()
{
	if (ULoopstone_Island_SaveGame* SaveGameInstance = Cast<ULoopstone_Island_SaveGame>(
		UGameplayStatics::CreateSaveGameObject(ULoopstone_Island_SaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->PlayerName = TEXT("PlayerOne");
		SaveGameInstance->bCollectedLoopstones = bCollectedLoopstones;
		SaveGameInstance->bIsUsingController = bUsingController;

		// Save the data immediately.
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, "TestSave", 0))
		{
			// Save succeeded.
		}
	}
}

void ALoopstone_IslandGameState::LoadGame()
{
	// GetWorld()->GetAuthGameMode()->ResetLevel();
	// Retrieve and cast the USaveGame object to UMySaveGame.
	if (ULoopstone_Island_SaveGame* LoadedGame = Cast<ULoopstone_Island_SaveGame>(
		UGameplayStatics::LoadGameFromSlot("TestSave", 0)))
	{
		// The operation was successful, so LoadedGame now contains the data we saved earlier.
		UE_LOG(LogTemp, Warning, TEXT("LOADED: %s"), *LoadedGame->PlayerName);
		bCollectedLoopstones = LoadedGame->bCollectedLoopstones;
		bUsingController = LoadedGame->bIsUsingController;
		bEventHasBeenTriggered[static_cast<int>(EEventType::TutorialCompleted)] = bCollectedLoopstones[static_cast<int>(
			EStory::Detective)];
	}
}

void ALoopstone_IslandGameState::CollectLoopstone(EStory StoryOwningLoopstone)
{
	bCollectedLoopstones[static_cast<int>(StoryOwningLoopstone)] = true;
	SaveGame();

	// check if all loopstones are collected
	// if they are do the thing where you play the rest of the story

	if (StoryOwningLoopstone == EStory::Detective)
	{
		// maybe something should happen with the machine??
		// will probably happen in the interactive object and not here though
	}
	else if (StoryOwningLoopstone == EStory::PartyPlanner)
	{
		Machine->DisplayLoopstone(EStory::PartyPlanner);
	}
	else
	{
		// do stuff to show collected loopstone?
		// should probably be in the actual loopstone object
		UGameplayStatics::OpenLevel(this, "Fullday");
	}
}

bool ALoopstone_IslandGameState::TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction)
{
	bEventHasBeenTriggered[static_cast<int>(EventType)] = NewBoolValue;

	UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(EventType),
	       (NewBoolValue ? TEXT("true") : TEXT("false")));

	if (!InventoryWidget)
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
		case EEventType::HasLighthouseKey: case EEventType::HasBoathouseKey:
			{
				InventoryWidget->EditInventoryItem(EItem::Key, NewBoolValue);
				break;
			}
		case EEventType::DoctorWalkingAway: // move doctor and end convo
			{
				if (IsValid(CurrentIslander))
				{
					TeleportDoctor(CurrentIslander);
				}

				break;
			}
		case EEventType::HasMachine:
			{
				CollectLoopstone(EStory::Detective);
				break;
			}
		default: ;
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
			InteractableObject->DoNotInteract();
			return false;
		}
	}
	for (auto Element : InteractableObject->TopicBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != this->bTopicHasBeenRevealed[static_cast<int>(Element.Key)])
		{
			InteractableObject->DoNotInteract();
			return false;
		}
	}

	if (InteractableObject->TimeOfDayCondition != ETimeOfDay::None &&
		InteractableObject->TimeOfDayCondition != this->CurrentTimeOfDay)
	{
		InteractableObject->DoNotInteract();
		return false;
	}
	if (InteractableObject->ActiveStoryCondition != EStory::None &&
		InteractableObject->ActiveStoryCondition != this->CurrentStory)
	{
		InteractableObject->DoNotInteract();
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
	float SecondsSinceLastDialogueClosed = UGameplayStatics::GetTimeSeconds(GetWorld()) - TimeLastDialogueClosed;
	if (!Islander || !DialogueWidget || SecondsSinceLastDialogueClosed < SecondsBeforeYouCanTalkToIslanderAgain)
	{
		return false;
	}

	if (Islander->Dialogue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue started with %s"), *Islander->Name);

		CurrentIslander = Islander;
		CurrentDialogue = Islander->Dialogue;
		Islander->ResetView();

		GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(true);
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(Islander, 0.5f);

		DialogueWidget->SetVisibility(ESlateVisibility::Visible);
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(GetWorld()->GetFirstPlayerController());
		// UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), DialogueWidget);
		// if (!bUsingController)
		// {
		// todo set mouse position to centre of screen or to where options spawn
		//
		if (bUsingController)
		{
			DialogueWidget->Button_MouseBlocker->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			DialogueWidget->Button_MouseBlocker->SetVisibility(ESlateVisibility::Hidden);
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GetWorld()->GetFirstPlayerController()->SetMouseLocation(500, 500);
		}
		// }
		CurrentDialogue->CurrentDialogueNode = nullptr;

		DialogueWidget->SetSpeakerName(Islander->Name);
		DialogueWidget->SetRichStyleText(Islander->RichTextStyles);
		DialogueWidget->StartDialogueAnimation(true);
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
	// swap camera
	GetWorld()->GetFirstPlayerController()->SetIgnoreMoveInput(false);
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(
		GetWorld()->GetFirstPlayerController()->GetPawn(), 0.5f);

	if (DialogueWidget)
	{
		// UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), DialogueWidget);
		CurrentIslander = nullptr;
		CurrentDialogue->CurrentDialogueNode = nullptr;
		CurrentDialogue = nullptr;

		//todo figure out if this can be done differently
		DialogueWidget->Button_Option000->SetVisibility(ESlateVisibility::Hidden);
		DialogueWidget->Dialogue_Text->SetText(FText::FromString(" "));

		DialogueWidget->StartDialogueAnimation(false);
		DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

		TimeLastDialogueClosed = UGameplayStatics::GetTimeSeconds(GetWorld());
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
	while (CurrentDialogue->CurrentDialogueNode->NodeExits == ENodeExits::Condition)
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
	if (CurrentDialogue->CurrentDialogueNode->bHasBeenVisited &&
		!CurrentDialogue->CurrentDialogueNode->DialogueTextOnRevisit.IsEmptyOrWhitespace())
	{
		DialogueText = CurrentDialogue->CurrentDialogueNode->DialogueTextOnRevisit.ToString();
	}
	else
	{
		DialogueText = CurrentDialogue->CurrentDialogueNode->DialogueText.ToString();
	}
	CurrentDialogue->CurrentDialogueNode->bHasBeenVisited = true;
	// Change facial expression on islander
	CurrentIslander->ChangeAnimation(CurrentDialogue->CurrentDialogueNode->Animation);
	CurrentIslander->ChangeMouthExpression(EMouthExpression::Mouth_Talk);
	CurrentIslander->ChangeEyeExpression(CurrentDialogue->CurrentDialogueNode->RightEyeExpression,
	                                     CurrentDialogue->CurrentDialogueNode->LeftEyeExpression);
	// Change animation??

	DialogueWidget->SetDialogueWithOptions(0.03f, DialogueText, CurrentDialogue->GetCurrentOptions(this));

	return true;
}

void ALoopstone_IslandGameState::ChangeTimeOfDay(ETimeOfDay NewTimeOfDay)
{
	CurrentTimeOfDay = NewTimeOfDay;
	if (SunSky)
	{
		SunSky->ChangeTimeOfDay(NewTimeOfDay);

		SunSky->ChangeSky(NewTimeOfDay);
		if (IsValid(TargetPointController))
		{
			TargetPointController->MoveIslandersToPosition(NewTimeOfDay, CurrentStory);
		}
	}
	for (auto Actors : MusicActors)
	{
		if (IsValid(Actors))
		{
			Actors->ChangeCurrentTimeOfDay(NewTimeOfDay);
		}
	}
}

void ALoopstone_IslandGameState::ChangeStory(EStory NewStory)
{
	CurrentStory = NewStory;

	// Do functionality if any.
}
