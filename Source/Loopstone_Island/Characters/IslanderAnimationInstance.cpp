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
		UE_LOG(LogTemp, Warning, TEXT("CURRENTLY LOOKING AT"));
	}
	else
	{

		APawn* Owner = TryGetPawnOwner();
		if(IsValid(Owner))
		{
			PlayerLocation = SelfLocation + (Owner->GetActorForwardVector() * 200);
		}
	}

	LookLocation = FMath::VInterpTo(LookLocation, PlayerLocation, DeltaTime, LookAtSpeed);
	Rotation = UKismetMathLibrary::FindLookAtRotation(SelfLocation, LookLocation);
	Rotation.Roll = (Rotation.Pitch * -1) + 90;
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
	auto owner =Cast<ABaseIslanderCharacter>(TryGetPawnOwner());
	if(IsValid(owner))
	{
		SelfLocation = owner->GetMesh()->GetSocketLocation("Head");
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
