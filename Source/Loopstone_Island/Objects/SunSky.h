// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Systems/Loopstone_IslandGameState.h"
#include "SunSky.generated.h"

UENUM(BlueprintType)
enum class ESkyProperties : uint8
{
	Time,
	CloudOpacity,
	StarOpacity
};

UCLASS()
class LOOPSTONE_ISLAND_API ASunSky : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASunSky();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> SolarTimes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> CloudOpacities;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> StarOpacities;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeTimeOfDay(ETimeOfDay TimeOfDay);

	UFUNCTION(BlueprintCallable)
	float GetNewValue(ETimeOfDay NewTimeOfDay, float Percent, ESkyProperties PropertyToCheck);

private:
	TArray<float> SolarTimeScales;
	TArray<float> CloudOpacityScales;
	TArray<float> StarOpacityScales;
};
