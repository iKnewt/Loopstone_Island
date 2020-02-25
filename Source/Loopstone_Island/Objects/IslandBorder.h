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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USplineComponent* Spline = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAudioComponent* Waves = nullptr;

	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AudioTimer = 0.25f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateAudioComponentLocation();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
