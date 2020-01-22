// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseIslanderCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseIslanderCharacter::ABaseIslanderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	MouthPlate = CreateDefaultSubobject<UStaticMeshComponent>(FName("MouthPlate"));
	EyePlate = CreateDefaultSubobject<UStaticMeshComponent>(FName("EyePlate"));
	MouthPlate->SetupAttachment(GetMesh(),FName("HeadSocket"));
	EyePlate->SetupAttachment(GetMesh(),FName("HeadSocket"));
}

// Called when the game starts or when spawned
void ABaseIslanderCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseIslanderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseIslanderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

