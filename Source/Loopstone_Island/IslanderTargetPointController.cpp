// Fill out your copyright notice in the Description page of Project Settings.


#include "IslanderTargetPointController.h"
#include "Kismet/GameplayStatics.h"
#include "IslanderTargetPoint.h"
#include "BaseIslanderCharacter.h"

// Sets default values
AIslanderTargetPointController::AIslanderTargetPointController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AIslanderTargetPointController::MoveIslandersToPosition(ETimeOfDay NewTimeOfDay)
{
	for(int i = 0; i < Islanders.Num(); i++)
	{
		if(IsValid(Islanders[i]))
		{
				if(IsValid(Points[i][int32(NewTimeOfDay)]))
				{
					Islanders[i]->SetActorLocation(Points[i][int32(NewTimeOfDay)]->GetActorLocation());
					Islanders[i]->SetActorRotation(Points[i][int32(NewTimeOfDay)]->GetActorRotation());
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
	for(int i = 0; i < Islanders.Num(); i++)
	{
		if(IsValid(Islanders[i]))
		{
			UE_LOG(LogTemp, Error, TEXT("VALUE: %i"), int32(Islanders[i]->IslanderType));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AYO NOTHING HERE "));
		}

	}
	for(int i = 0; i < Points.Num(); i++)
	{
		for(int j = 0; j < Points[i].Num(); j++)
		{
			UE_LOG(LogTemp, Error, TEXT("THING: %i, THING2: %i"),i,j);
		}
	}
}

void AIslanderTargetPointController::SetupIslandersArray()
{
	Islanders.Init(nullptr, int32(EIslanderType::None));
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseIslanderCharacter::StaticClass(), Actors);
	for(int i = 0; i < Actors.Num(); i++)
	{
		auto Islander = Cast<ABaseIslanderCharacter>(Actors[i]);
		if(IsValid(Islander))
		{
			if(Islander->IslanderType != EIslanderType::None)
			{
				Islanders[int32(Islander->IslanderType)] = Islander;
			}
		}
	}
}

void AIslanderTargetPointController::SetupIslandPositions()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AIslanderTargetPoint::StaticClass(), Actors);
	int32 NumberOfIslanders = int32(EIslanderType::None);
	int32 TimeOfDays = int32(ETimeOfDay::None);
	TArray<AIslanderTargetPoint*> x;
	x.Init(nullptr, TimeOfDays);
	Points.Init(x, NumberOfIslanders);
	for(int i = 0; i < Actors.Num(); i++)
	{
		auto Point = Cast<AIslanderTargetPoint>(Actors[i]);
		if(IsValid(Point))
		{
			Points[int32(Point->Islander)][int32(Point->TimeOfDay)] = Point;
		}
	}
}

// Called every frame
void AIslanderTargetPointController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

