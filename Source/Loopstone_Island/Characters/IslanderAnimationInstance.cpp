// Fill out your copyright notice in the Description page of Project Settings.


#include "IslanderAnimationInstance.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BaseIslanderCharacter.h"
#include "Kismet/KismetMathLibrary.h"


void UIslanderAnimationInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	ResetLocationVectors();
}

void UIslanderAnimationInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	UpdateLookAt(DeltaTime);
}

void UIslanderAnimationInstance::UpdateLookAt(float DeltaTime)
{
	FVector PlayerLocation;
	
	if(bLookAt)
	{
		PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	}
	else
	{
		APawn* Owner = TryGetPawnOwner();
		if(Owner)
		{
			PlayerLocation = SelfLocation + (Owner->GetActorForwardVector() * 200);
		}
	}

	LookLocation = FMath::VInterpTo(LookLocation, PlayerLocation, DeltaTime, LookAtSpeed);
	Rotation = UKismetMathLibrary::FindLookAtRotation(SelfLocation, LookLocation);

	//Has to do some strange things as to make it work here
	Rotation.Roll = (Rotation.Pitch * -1);
	Rotation.Pitch = 0;
	Rotation.Yaw = Rotation.Yaw - ZRotation;
	Rotation =	Rotation.Clamp();
	if(Rotation.Yaw > 180)
	{
		Rotation.Yaw = FMath::Clamp(Rotation.Yaw, 360.f - TurnAmount, 360.f);
	}
	else
	{
		Rotation.Yaw = FMath::Clamp(Rotation.Yaw, 0.f, TurnAmount);
	}

}

void UIslanderAnimationInstance::ResetLocationVectors()
{
	//Casting needed as to get skeletal mesh
	auto Owner =Cast<ABaseIslanderCharacter>(TryGetPawnOwner());
	if(IsValid(Owner))
	{
		SelfLocation = Owner->GetMesh()->GetSocketLocation("Head");
	}
	else
	{
		SelfLocation = TryGetPawnOwner()->GetActorLocation();
	}

	LookLocation = SelfLocation + (TryGetPawnOwner()->GetActorForwardVector() * 200);
	ZRotation = TryGetPawnOwner()->GetActorRotation().Yaw;
}

void UIslanderAnimationInstance::LookAt(bool Activate)
{
	bLookAt = Activate;
}
