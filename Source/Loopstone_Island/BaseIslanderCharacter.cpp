// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseIslanderCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

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

void ABaseIslanderCharacter::ChangeMouthExpression(const EMouthExpression MouthExpression)
{
	if(!IsValid(MouthPlateMaterial))
	{
		//Only needs to be done once.
		CreateDynamicFaceMaterials();
	}
	MouthPlateMaterial->SetScalarParameterValue("MouthExpression", int(MouthExpression));
}

void ABaseIslanderCharacter::ChangeEyeExpression(const EEyeExpression EyeExpression)
{
	if(!IsValid(EyePlateMaterial))
	{
		//Only Needs to be done once.
		CreateDynamicFaceMaterials();
	}
	EyePlateMaterial->SetScalarParameterValue("EyeExpression", int(EyeExpression));

}

void ABaseIslanderCharacter::CreateDynamicFaceMaterials()
{
	EyePlateMaterial = UMaterialInstanceDynamic::Create(EyePlate->GetMaterial(0),this);
	MouthPlateMaterial = UMaterialInstanceDynamic::Create(MouthPlate->GetMaterial(0), this);
	EyePlate->SetMaterial(0, EyePlateMaterial);
	MouthPlate->SetMaterial(0, MouthPlateMaterial);
}



