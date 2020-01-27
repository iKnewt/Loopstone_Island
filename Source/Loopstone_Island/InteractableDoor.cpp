// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractableDoor::AInteractableDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DoorMesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneRoot"));
	DoorMesh->AttachTo(RootComponent);
}

void AInteractableDoor::PlayAnimation()
{
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("UpdateAnimation"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		if(!bOpened)
		{
			CurveTimeline.PlayFromStart();
		}
		else
		{
			CurveTimeline.ReverseFromEnd();
		}
		bOpened = !bOpened;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR: No CurveFloat set!"));
	}
}

void AInteractableDoor::UpdateAnimation(float Value)
{
	if(bOpenInwards)
	{
		RootComponent->SetRelativeRotation(FRotator(0, Value, 0));
	}
	else
	{
			RootComponent->SetRelativeRotation(FRotator(0, Value*-1, 0));
	}

}

void AInteractableDoor::Interact()
{
	PlayAnimation();
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

