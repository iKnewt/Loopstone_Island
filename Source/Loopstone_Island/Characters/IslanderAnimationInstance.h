// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameStateEnums.h"
#include "IslanderAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API UIslanderAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	void UpdateLookAt(float DeltaTime);
	bool bLookAt = false;

	FVector SelfLocation;
	FVector LookLocation;
	//Used in animation blueprint to modify bone
	UPROPERTY(BlueprintReadOnly)
		FRotator Rotation;
	UPROPERTY(EditAnywhere)
		float LookAtSpeed = 3.f;

	//How much the owning actor is allowed to turn their head.
	UPROPERTY(EditAnywhere)
		float TurnAmount = 70.f;
	//How much the owning actor is rotated around the Z/Yaw axis.
	float ZRotation;
public:
	//Activates look at player functionality.
	void LookAt(bool Activate);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		EAnimations CurrentAnimation = EAnimations::Idle;
	void ResetLocationVectors();
};
