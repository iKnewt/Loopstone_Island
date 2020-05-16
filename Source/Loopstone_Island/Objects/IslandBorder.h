// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IslandBorder.generated.h"

UCLASS()
class LOOPSTONE_ISLAND_API AIslandBorder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIslandBorder();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Moves the audio component based on players location to spline
	void UpdateAudioComponentLocation();

	//~=============================================================================
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USplineComponent* Spline = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAudioComponent* Waves = nullptr;
	USceneComponent* Root;

	//Timer to move the audio component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AudioTimer = 0.25f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
