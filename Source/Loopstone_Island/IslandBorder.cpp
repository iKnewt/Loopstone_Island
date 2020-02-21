// Fill out your copyright notice in the Description page of Project Settings.

#include "IslandBorder.h"
#include "Components/SplineComponent.h"
#include "Components/AudioComponent.h"


// Sets default values
AIslandBorder::AIslandBorder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Waves = CreateDefaultSubobject<UAudioComponent>(TEXT("Waves"));

}

// Called when the game starts or when spawned
void AIslandBorder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIslandBorder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

