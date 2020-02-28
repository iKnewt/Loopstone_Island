// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/AmbientSound.h"
#include "GameStateEnums.h"
#include "Components/TimelineComponent.h"
#include "IslandAmbientSound.generated.h"

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API AIslandAmbientSound : public AAmbientSound
{
	GENERATED_BODY()
public:
	AIslandAmbientSound();
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	void ChangeCurrentTimeOfDay(ETimeOfDay TimeOfDay);
	ETimeOfDay CurrentTimeOfDay;
	void StartSoundTransition(bool Forwards);

	UFUNCTION()
	void UpdateSoundVolume(float Value);
	UFUNCTION()
	void SetNewSound();

	UPROPERTY(Category = "Sound Selection", EditAnywhere)
		uint32 bDynamicAudioBasedOnTimeOfDay : 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Sound Selection", meta = (EditCondition = "bDynamicAudioBasedOnTimeOfDay"))
		USoundBase* MorningSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Selection", meta = (EditCondition = "bDynamicAudioBasedOnTimeOfDay"))
		USoundBase* AfternoonSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Selection", meta = (EditCondition = "bDynamicAudioBasedOnTimeOfDay"))
		USoundBase* EveningSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Selection", meta = (EditCondition = "bDynamicAudioBasedOnTimeOfDay"))
		USoundBase* NightSound;


	UPROPERTY(Category = "Timeline", EditAnywhere)
		uint32 bTransition : 1;
	UPROPERTY(EditAnywhere, Category = "Timeline", meta = (EditCondition = "bTransition"))
		UCurveFloat* CurveFloat;
		FTimeline CurveTimeline;
};
