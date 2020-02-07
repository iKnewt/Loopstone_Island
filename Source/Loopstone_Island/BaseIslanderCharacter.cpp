// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseIslanderCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseIslanderCharacter::ABaseIslanderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	RightEye = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("RightEye"));
	LeftEye = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("LeftEye"));
	Mouth = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("MouthPlate"));
	RightEye->SetupAttachment(GetMesh(),FName("HeadSocket"));
	LeftEye->SetupAttachment(GetMesh(),FName("HeadSocket"));
	Mouth->SetupAttachment(GetMesh(), FName("HeadSocket"));
}

// Called when the game starts or when spawned
void ABaseIslanderCharacter::BeginPlay()
{
	Super::BeginPlay();
	RightEye->PlayFromStart();
	LeftEye->PlayFromStart();
	Mouth->PlayFromStart();
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
	switch(MouthExpression)
	{
	case EMouthExpression::Mouth_Talk:
		Mouth->SetFlipbook(Mouth_Talk);
		break;
	case EMouthExpression::Mouth_Smile:
		Mouth->SetFlipbook(Mouth_Smile);
		break;
	default: ;
	}
	Mouth->PlayFromStart();
}

void ABaseIslanderCharacter::ChangeEyeExpression(EEyeExpression RightEyeExpression, EEyeExpression LeftEyeExpression)
{
	UE_LOG(LogTemp, Warning, TEXT("CHANGING EYE"))
	switch (RightEyeExpression)
	{
	case EEyeExpression::Eye_Open:
		RightEye->SetFlipbook(OpenEye);
		UE_LOG(LogTemp, Warning, TEXT("EYE OPEN"))
		break;
	case EEyeExpression::Eye_Blinking:
		UE_LOG(LogTemp, Warning, TEXT("EYE BLINKING"))
		RightEye->SetFlipbook(Blinking);
		break;
	default: ;
	}
	switch(LeftEyeExpression)
	{
	case EEyeExpression::Eye_Open:
		LeftEye->SetFlipbook(OpenEye);
		break;
	case EEyeExpression::Eye_Blinking:
		LeftEye->SetFlipbook(Blinking);
		break;
	default: ;
	}
	RightEye->PlayFromStart();
	LeftEye->PlayFromStart();
}


