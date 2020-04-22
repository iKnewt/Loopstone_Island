// Fill out your copyright notice in the Description page of Project Settings.


#include "SunSky.h"
// #include "Loopstone_IslandGameModeBase.h"

// Sets default values
ASunSky::ASunSky()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SolarTimeScales.SetNum(4);
	CloudOpacityScales.SetNum(4);
	StarOpacityScales.SetNum(4);
	SolarTimes.SetNum(4);
	CloudOpacities.SetNum(4);
	StarOpacities.SetNum(4);
}

// Called when the game starts or when spawned
void ASunSky::BeginPlay()
{
	Super::BeginPlay();

	ALoopstone_IslandGameState* GameState = dynamic_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState());
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("CORRECT GAME STATE NOT FOUND IN SUNSKY"));
	}
	else
	{
		GameState->SunSky = this;
	}

	for (int i = 0; i < 4; i++)
	{
		int j = i - 1;
		if (j == -1) { j = 3; }

		if (i == 0)
		{
			SolarTimeScales[i] = SolarTimes[i] - 4;
		}
		else
		{
			SolarTimeScales[i] = SolarTimes[i] - SolarTimes[j];
		}

		CloudOpacityScales[i] = CloudOpacities[i] - CloudOpacities[j];
		StarOpacityScales[i] = StarOpacities[i] - StarOpacities[j];
	}
}

// Called every frame
void ASunSky::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ASunSky::GetNewValue(ETimeOfDay NewTimeOfDay, float Percent, ESkyProperties PropertyToCheck)
{
	int OldTime = static_cast<int>(NewTimeOfDay) - 1;
	if (OldTime == -1) { OldTime = 3; }

	switch (PropertyToCheck)
	{
	case ESkyProperties::Time:
		if (NewTimeOfDay == ETimeOfDay::Morning)
		{
			return SolarTimeScales[static_cast<int>(NewTimeOfDay)] * Percent + 4;
		}
		else
		{
			return SolarTimeScales[static_cast<int>(NewTimeOfDay)] * Percent + SolarTimes[OldTime];
		}
	case ESkyProperties::CloudOpacity:
		return CloudOpacityScales[static_cast<int>(NewTimeOfDay)] * Percent + CloudOpacities[OldTime];
	case ESkyProperties::StarOpacity:
		return StarOpacityScales[static_cast<int>(NewTimeOfDay)] * Percent + StarOpacities[OldTime];
	default:
		return 0;
	}
}
