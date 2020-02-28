// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStateEnums.h"
#include "Components/TimelineComponent.h"

#include "IslandSound.generated.h"

UCLASS()
class LOOPSTONE_ISLAND_API AIslandSound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandSound();
	UPROPERTY(Category = "Sound Selection", EditAnywhere)
		uint32 bDynamicAudioBasedOnTimeOfDay : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Selection", meta = (EditCondition = "bDynamicAudioBasedOnTimeOfDay"))
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
	FTimeline GainTimeline;
	FTimeline DownTimeline;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category= "Audio Component")
	class UAudioComponent* AudioComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeCurrentTimeOfDay(ETimeOfDay TimeOfDay);
	ETimeOfDay CurrentTimeOfDay;
	void StartSoundTransition();

	void EndSoundTransition();

	UFUNCTION()
		void UpdateSoundVolume(float Value);
	UFUNCTION()
		void SetNewSound();




};
