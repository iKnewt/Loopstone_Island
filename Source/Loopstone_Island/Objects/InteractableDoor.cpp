// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"


// Sets default values
AInteractableDoor::AInteractableDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractableDoor::PlayAnimation()
{
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("UpdateAnimation"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		if (!bOpened)
		{
			CurveTimeline.Play();
			if(IsValid(DoorOpen))
			{
				Sound->SetSound(DoorOpen);
			}
			GetWorldTimerManager().SetTimer(DoorTimer, this, &AInteractableDoor::PlayAnimation, 7, false);
		}
		else
		{
			CurveTimeline.Reverse();
			if (IsValid(DoorClose))
			{
				Sound->SetSound(DoorClose);

			}
			if (GetWorldTimerManager().IsTimerActive(DoorTimer))
			{
				GetWorldTimerManager().ClearTimer(DoorTimer);
			}
		}
		bOpened = !bOpened;
		Sound->Play();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: No CurveFloat set!"));
	}
}

void AInteractableDoor::UpdateAnimation(float Value)
{
	float Modifier = 1.f;
	if(bOpenInwards)
	{
		Modifier = -1.f;
	}
		RootComponent->SetRelativeRotation(FRotator(0, Value * Modifier, 0));
}

void AInteractableDoor::Interact()
{
	PlayAnimation();
}

void AInteractableDoor::DoNotInteract()
{
	if(IsValid(DoorLocked))
	{
		Sound->SetSound(DoorLocked);
		Sound->Play();
	}

}

// Called when the game starts or when spawned
void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
}
