// Fill out your copyright notice in the Description page of Project Settings.


#include "IslanderTargetPointController.h"
#include "Kismet/GameplayStatics.h"
#include "IslanderTargetPoint.h"
#include "Characters/BaseIslanderCharacter.h"

// Sets default values
AIslanderTargetPointController::AIslanderTargetPointController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AIslanderTargetPointController::MoveIslandersToPosition(ETimeOfDay NewTimeOfDay, EStory CurrentStory)
{
	if (CurrentStory != EStory::None)
	{
		for (int i = 0; i < Islanders.Num(); i++)
		{
			if (IsValid(Islanders[i]))
			{
				if (IsValid(Points[static_cast<int32>(CurrentStory)][i][static_cast<int32>(NewTimeOfDay)]))
				{
					Islanders[i]->SetActorLocation(
						Points[static_cast<int32>(CurrentStory)][i][static_cast<int32>(NewTimeOfDay)]->
						GetActorLocation());
					Islanders[i]->SetActorRotation(
						Points[static_cast<int32>(CurrentStory)][i][static_cast<int32>(NewTimeOfDay)]->
						GetActorRotation());
					Islanders[i]->ResetView();
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void AIslanderTargetPointController::BeginPlay()
{
	Super::BeginPlay();
	SetupIslandersArray();
	SetupIslandPositions();
}

void AIslanderTargetPointController::SetupIslandersArray()
{
	Islanders.Init(nullptr, static_cast<int32>(EIslanderType::None));
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseIslanderCharacter::StaticClass(), Actors);
	for (int i = 0; i < Actors.Num(); i++)
	{
		auto Islander = Cast<ABaseIslanderCharacter>(Actors[i]);
		if (IsValid(Islander))
		{
			if (Islander->IslanderType != EIslanderType::None)
			{
				Islanders[static_cast<int32>(Islander->IslanderType)] = Islander;
			}
		}
	}
}

void AIslanderTargetPointController::SetupIslandPositions()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIslanderTargetPoint::StaticClass(), Actors);

	int32 NumberOfIslanders = static_cast<int32>(EIslanderType::None);
	int32 TimeOfDays = static_cast<int32>(ETimeOfDay::None);


	//Setting up the inner TArray
	TArray<AIslanderTargetPoint*> TargetPoints;
	TargetPoints.Init(nullptr, TimeOfDays);

	//Setting up the middle TArray
	TArray<TArray<class AIslanderTargetPoint*>> Islander;
	Islander.Init(TargetPoints, NumberOfIslanders);

	Points.Init(Islander, static_cast<int32>(EStory::None));

	for (int i = 0; i < Actors.Num(); i++)
	{
		auto Point = Cast<AIslanderTargetPoint>(Actors[i]);
		if (IsValid(Point))
		{
			Points[static_cast<int32>(Point->Story)][static_cast<int32>(Point->Islander)][static_cast<int32>(Point->
				TimeOfDay)] = Point;
		}
	}
}
