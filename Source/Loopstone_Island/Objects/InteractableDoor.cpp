// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


// Sets default values
AInteractableDoor::AInteractableDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractableDoor::CloseDoorSound()
{
	if(!bOpened)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorSlam, GetActorLocation(), GetActorRotation(), 1, 1, 0, Sound->AttenuationSettings);
		Sound->Stop();
	}

}

void AInteractableDoor::PlayAnimation()
{
	
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		FOnTimelineEventStatic TimelineEnd;
		TimelineEnd.BindUFunction(this, "CloseDoorSound");
		TimelineProgress.BindUFunction(this, FName("UpdateAnimation"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetTimelineFinishedFunc(TimelineEnd);
		
		if (!bOpened)
		{
			CurveTimeline.Play();
			if(IsValid(DoorOpen))
			{
				Sound->SetSound(DoorOpen);
			}
			if(bAutoClose)
			{
				GetWorldTimerManager().SetTimer(DoorTimer, this, &AInteractableDoor::PlayAnimation, 7, false);
			}
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
	if (bDoorAlwaysLocked)
	{
		DoNotInteract();
	}
	else
 {
		bDoorLockedNow = false;
		
		auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (IsValid(Player))
		{
			//The front of the door, relative to world, not local object
			FVector Front = GetActorRightVector();
			FVector PlayerForwardVector = Player->GetActorForwardVector();
			float direction = FVector::DotProduct(Front, PlayerForwardVector);
			//if direction is positive, open inwards
			if (!CurveTimeline.IsPlaying())
			{
				if (direction > 0)
				{
					bOpenInwards = true;
				}
				else
				{
					bOpenInwards = false;
				}
			}
		}
		PlayAnimation();
	}
}

void AInteractableDoor::DoNotInteract()
{
	if (bDoorAlwaysLocked || bDoorLockedNow)
	{
		if (IsValid(DoorLocked))
		{
			Sound->SetSound(DoorLocked);
			Sound->Play();
		}
	}
	else
	{
		Interact();
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
