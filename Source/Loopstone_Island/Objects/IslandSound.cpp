// Fill out your copyright notice in the Description page of Project Settings.


#include "IslandSound.h"
#include "Components/AudioComponent.h"
#include "Loopstone_IslandGameState.h"

// Sets default values
AIslandSound::AIslandSound()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void AIslandSound::StopAudio()
{
	AudioComponent->Stop();
}

// Called when the game starts or when spawned
void AIslandSound::BeginPlay()
{
	Super::BeginPlay();
	ALoopstone_IslandGameState* GameState = Cast<ALoopstone_IslandGameState>(GetWorld()->GetGameState());
	if (IsValid(GameState))
	{
		GameState->MusicActors.Add(this);
	}

	FOnTimelineFloat TimelineProgress;
	TimelineProgress.BindUFunction(this, FName("UpdateSoundVolume"));
	GainTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
	FOnTimelineEventStatic TimelineFinishedCallback;
	TimelineFinishedCallback.BindUFunction(this, FName("SetNewSound"));
	GainTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	DownTimeline.AddInterpFloat(CurveFloat, TimelineProgress);

	CurrentTimeOfDay = ETimeOfDay::Morning;
}

// Called every frame
void AIslandSound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GainTimeline.TickTimeline(DeltaTime);
	DownTimeline.TickTimeline(DeltaTime);
}

void AIslandSound::ChangeCurrentTimeOfDay(ETimeOfDay TimeOfDay)
{
	if (bDynamicAudioBasedOnTimeOfDay)
	{
		CurrentTimeOfDay = TimeOfDay;
		StartSoundTransition();
	}
}

void AIslandSound::StartSoundTransition()
{
	UE_LOG(LogTemp, Warning, TEXT("STARTING SOUND TRANSITION"));
	if (bTransition)
	{
		GainTimeline.PlayFromStart();
	}
	else
	{
		SetNewSound();
	}
}

void AIslandSound::EndSoundTransition()
{
	UE_LOG(LogTemp, Warning, TEXT("ENDING SOUND TRANSITION"));
	DownTimeline.ReverseFromEnd();
}

void AIslandSound::UpdateSoundVolume(float Value)
{
	AudioComponent->SetVolumeMultiplier(Value);
}

void AIslandSound::SetNewSound()
{
	switch (CurrentTimeOfDay)
	{
	case ETimeOfDay::Morning:
		if (IsValid(MorningSound))
		{
			AudioComponent->SetSound(MorningSound);
		}
		break;
	case ETimeOfDay::Afternoon:
		if (IsValid(AfternoonSound))
		{
			AudioComponent->SetSound(AfternoonSound);
		}
		break;
	case ETimeOfDay::Evening:
		if (IsValid(EveningSound))
		{
			AudioComponent->SetSound(EveningSound);
		}
		break;
	case ETimeOfDay::Night:
		if (IsValid(NightSound))
		{
			AudioComponent->SetSound(NightSound);
		}
		break;
	}
	if (!AudioComponent->IsPlaying())
	{
		AudioComponent->Play();
		AudioComponent->SetVolumeMultiplier(0.f);
	}
	if (bTransition)
	{
		EndSoundTransition();
	}
}
