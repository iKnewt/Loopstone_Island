// Fill out your copyright notice in the Description page of Project Settings.


#include "IslandAmbientSound.h"
#include "Loopstone_IslandGameState.h"
#include "Components/AudioComponent.h"

AIslandAmbientSound::AIslandAmbientSound()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIslandAmbientSound::BeginPlay()
{
	
	ALoopstone_IslandGameState* GameState = Cast<ALoopstone_IslandGameState>(GetWorld()->GetGameState());
	if(IsValid(GameState))
	{
		GameState->MusicActor = this;
	}

	if(bDynamicAudioBasedOnTimeOfDay)
	{
		GetAudioComponent()->SetSound(MorningSound);
	}
	GetAudioComponent()->Play();
}

void AIslandAmbientSound::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurveTimeline.TickTimeline(DeltaSeconds);
}

void AIslandAmbientSound::ChangeCurrentTimeOfDay(ETimeOfDay TimeOfDay)
{
	if(bDynamicAudioBasedOnTimeOfDay)
	{
		CurrentTimeOfDay = TimeOfDay;
		StartSoundTransition(true);
	}
}

void AIslandAmbientSound::StartSoundTransition(bool Forwards)
{
	UE_LOG(LogTemp, Warning, TEXT("STARTING SOUND TRANSITION"));
	if(bTransition)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("UpdateSoundVolume"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		if(Forwards)
		{
			FOnTimelineEventStatic TimelineFinishedCallback;
			TimelineFinishedCallback.BindUFunction(this, FName("SetNewSound"));
			CurveTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
			CurveTimeline.PlayFromStart();
		}
		else
		{
			CurveTimeline.ReverseFromEnd();
		}
	}
	else
	{
		SetNewSound();
	}
}

void AIslandAmbientSound::UpdateSoundVolume(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("SETTING VOLUME"));
	GetAudioComponent()->SetVolumeMultiplier(Value);
}

void AIslandAmbientSound::SetNewSound()
{
	switch (CurrentTimeOfDay)
	{
	case ETimeOfDay::Morning:
		GetAudioComponent()->SetSound(MorningSound);
		break;
	case ETimeOfDay::Afternoon:
		GetAudioComponent()->SetSound(AfternoonSound);
		break;
	case ETimeOfDay::Evening:
		GetAudioComponent()->SetSound(EveningSound);
		break;
	case ETimeOfDay::Night:
		GetAudioComponent()->SetSound(NightSound);
		break;
	}
	if(bTransition)
	{
		StartSoundTransition(false);
	}
}
