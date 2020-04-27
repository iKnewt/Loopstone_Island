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
#include "StoryDecor.h"
#include "Button.h"
#include "Characters/BaseIslanderCharacter.h"

void ALoopstone_IslandGameState::BeginPlay()
{
	Super::BeginPlay();

	// setting up conditions

	TimeLastDialogueClosed = UGameplayStatics::GetTimeSeconds(GetWorld());
	UE_LOG(LogTemp, Warning, TEXT("Besinning play"));
	ChangeTimeOfDay(ETimeOfDay::Morning);
	UE_LOG(LogTemp, Warning, TEXT("morning started"));

	bEventHasBeenTriggered.SetNum(static_cast<int>(EEventType::None) + 1);
	SetAllItemsInBoolArray(bEventHasBeenTriggered, false);
	UE_LOG(LogTemp, Warning, TEXT("bEventHasBeenTriggered contains:  %i"), bEventHasBeenTriggered.Num());
	bTopicHasBeenRevealed.SetNum(static_cast<int>(ETopic::None) + 1);
	SetAllItemsInBoolArray(bTopicHasBeenRevealed, false);
	UE_LOG(LogTemp, Warning, TEXT("bTopicHasBeenRevealed contains:  %i"), bTopicHasBeenRevealed.Num());
	bInventoryItemsCollected.SetNum(static_cast<int>(EInventoryItem::None) + 1);
	SetAllItemsInBoolArray(bInventoryItemsCollected, false);
	UE_LOG(LogTemp, Warning, TEXT("bInventoryItemsCollected contains:  %i"), bInventoryItemsCollected.Num());

	bCollectedLoopstones.SetNum(static_cast<int>(EStory::None));
	SetAllItemsInBoolArray(bCollectedLoopstones, false);
	UE_LOG(LogTemp, Warning, TEXT("bCollectedLoopstones contains:  %i"), bCollectedLoopstones.Num());

	// setting up widgets

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


	// test done to try to remove mouse cursor when UI only
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
		SaveGameInstance->PlayTimeSeconds = GetSecondsPlayed();

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
		PlayTimeSeconds = LoadedGame->PlayTimeSeconds;
		bEventHasBeenTriggered[static_cast<int>(EEventType::TutorialCompleted)] = bCollectedLoopstones[static_cast<int>(
			EStory::Detective)];
	}
}

void ALoopstone_IslandGameState::CollectLoopstone(EStory StoryOwningLoopstone)
{
	UE_LOG(LogTemp, Error, TEXT("COLLECT NAO"));

	if(StoryOwningLoopstone == EStory::None)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't collect loopstone when no story is selected"));
		return;
	}

	bCollectedLoopstones[static_cast<int>(StoryOwningLoopstone)] = true;
	SaveGame();

	if (StoryOwningLoopstone != EStory::Detective)
	{
		Machine->DisplayLoopstone(StoryOwningLoopstone);
		bool bAllLoopstonesCollected = true;

		for (bool bLoopstone : bCollectedLoopstones)
		{
			if(!bLoopstone)
			{
				bAllLoopstonesCollected = false;
				break;
			}
		}
		
		if (!bAllLoopstonesCollected)
		{
			UGameplayStatics::OpenLevel(this, "Fullday");
		}
	}
}

void ALoopstone_IslandGameState::StopAllMusic()
{
	for (auto Actors : MusicActors)
	{
		if (IsValid(Actors))
		{
			Actors->StopAudio();
		}
	}
}

bool ALoopstone_IslandGameState::CollectedAllLoopstones()
{
	return (bCollectedLoopstones[uint8(EStory::PartyPlanner)] && 
		bCollectedLoopstones[uint8(EStory::AssistantChef)] && 
		bCollectedLoopstones[uint8(EStory::Psychologist)]);
}

float ALoopstone_IslandGameState::GetSecondsPlayed()
{	
	UE_LOG(LogTemp, Warning, TEXT("Map Name: %s"), *GetWorld()->GetMapName());
	if (GetWorld()->GetMapName().Contains("Fullday"))
	{
		return PlayTimeSeconds + GetWorld()->GetTimeSeconds();
	}
	else 
	{
		return PlayTimeSeconds;
	}
}

bool ALoopstone_IslandGameState::ConditionsMet(TMap<ETopic, bool> TopicBoolsConditions,
                                               TMap<EEventType, bool> EventBoolsConditions,
                                               TMap<EInventoryItem, bool> IventoryBoolsConditions,
                                               ETimeOfDay TimeOfDayCondition, EStory ActiveStoryCondition)
{
	for (auto Element : TopicBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != bTopicHasBeenRevealed[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}
	for (auto Element : EventBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != bEventHasBeenTriggered[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}
	for (auto Element : IventoryBoolsConditions)
	{
		// if any element doesn't match the library it shouldn't display
		if (Element.Value != bInventoryItemsCollected[static_cast<int>(Element.Key)])
		{
			return false;
		}
	}

	// if the time of day doesn't match condition
	if (TimeOfDayCondition != ETimeOfDay::None &&
		TimeOfDayCondition != CurrentTimeOfDay)
	{
		return false;
	}
	if (ActiveStoryCondition != EStory::None &&
		ActiveStoryCondition != CurrentStory)
	{
		return false;
	}

	// if all conditions are met
	return true;
}

void ALoopstone_IslandGameState::ChangeConditions(TMap<ETopic, bool> TopicBoolsToChange,
                                                  TMap<EEventType, bool> EventBoolsToChange,
                                                  TMap<EInventoryItem, bool> IventoryBoolsChange,
                                                  ETimeOfDay TimeOfDayChange, EStory ActiveStoryChange)
{
	for (auto Element : TopicBoolsToChange)
	{
		bTopicHasBeenRevealed[static_cast<int>(Element.Key)] = Element.Value;
		UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(Element.Key),
			(Element.Value ? TEXT("true") : TEXT("false")));
	}
	for (const auto Element : EventBoolsToChange)
	{
		TriggerEvent(Element.Key, Element.Value);
	}
	for (const auto Element : IventoryBoolsChange)
	{	
		EditInventoryItem(Element.Key, Element.Value);
	}

	if (ActiveStoryChange != EStory::None)
	{
		ChangeStory(ActiveStoryChange);
	}
	if (TimeOfDayChange != ETimeOfDay::None)
	{
		ChangeTimeOfDay(TimeOfDayChange);
	}
}

void ALoopstone_IslandGameState::TriggerEvent(EEventType EventType, bool NewBoolValue, bool RunFunction)
{
	bEventHasBeenTriggered[static_cast<int>(EventType)] = NewBoolValue;
	UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(EventType),
	       (NewBoolValue ? TEXT("true") : TEXT("false")));

	if (RunFunction)
	{
		switch (EventType)
		{
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
		case EEventType::ChildDied:
			{
			auto doctor = TargetPointController->Islanders[uint8(EIslanderType::Doctor)];
				if(IsValid(doctor))
				{
					doctor->SetActorLocation(FVector(-3551.f, -3169.f, 635.f));
				}
			}
		default: ;
		}
	}
}

void ALoopstone_IslandGameState::EditInventoryItem(EInventoryItem Item, bool TrueToAddFalseToRemove)
{
	bInventoryItemsCollected[static_cast<int>(Item)] = TrueToAddFalseToRemove;
	UE_LOG(LogTemp, Warning, TEXT("%s set to %s"), *UEnum::GetValueAsString(Item),
	       (TrueToAddFalseToRemove ? TEXT("true") : TEXT("false")));
	
	if (InventoryWidget)
	{
		//todo fix better counter and also display in inventory menu 
		if (Item == EInventoryItem::Carrot)
		{
			if (TrueToAddFalseToRemove)
			{
				CarrotCount++;
			}
			else
			{
				// CarrotCount--;
				CarrotCount = 0;
			}
			if (CarrotCount >= 10)
			{
				bInventoryItemsCollected[static_cast<int>(EInventoryItem::Carrot)] = true;
			}
			else
			{
				bInventoryItemsCollected[static_cast<int>(EInventoryItem::Carrot)] = false;
			}
			InventoryWidget->SetCarrotCounter(CarrotCount);
		}
		
		InventoryWidget->EditInventoryItem(Item, TrueToAddFalseToRemove);
	}
}

bool ALoopstone_IslandGameState::InteractWithObject(AInteractableObjectBase* InteractableObject)
{
	if (ConditionsMet(InteractableObject->TopicBoolsConditions,
	                  InteractableObject->EventBoolsConditions,
	                  InteractableObject->InventoryBoolsConditions,
	                  InteractableObject->TimeOfDayCondition,
	                  InteractableObject->ActiveStoryCondition))
	{
		InteractableObject->Interact();
		ChangeConditions(InteractableObject->TopicBoolsToChange,
		                 InteractableObject->EventBoolsToChange,
		                 InteractableObject->InventoryBoolsChange,
		                 InteractableObject->TimeOfDayChange,
		                 InteractableObject->ActiveStoryChange);
		return true;
	}
	else
	{
		InteractableObject->DoNotInteract();
		return false;
	}
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
		// UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController());
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), DialogueWidget);
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

	ChangeConditions(CurrentDialogue->CurrentDialogueNode->TopicBoolsToChange,
	                 CurrentDialogue->CurrentDialogueNode->EventBoolsToChange,
	                 CurrentDialogue->CurrentDialogueNode->InventoryBoolsChange,
	                 CurrentDialogue->CurrentDialogueNode->TimeOfDayChange,
	                 CurrentDialogue->CurrentDialogueNode->ActiveStoryChange);

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
	for (auto Actor : StoryDecorActors)
	{
		if (Actor)
		{
			Actor->UnhideIfConditionsMet(NewTimeOfDay, CurrentStory);
		}
	}

	if(CurrentStory == EStory::Psychologist && CurrentTimeOfDay == ETimeOfDay::Night)
	{
		auto child = TargetPointController->Islanders[uint8(EIslanderType::Child)];
		child->ChangeAnimation(EAnimations::CustomAnimation1);
		child->ChangeEyeExpression(EEyeExpression::Eye_Calm, EEyeExpression::Eye_Calm);
		child->bLookAt = false;
	}
}

void ALoopstone_IslandGameState::ChangeStory(EStory NewStory)
{
	CurrentStory = NewStory;

	// Do functionality if any.
}
