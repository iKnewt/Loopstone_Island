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

	float ZRotation;
public:
	void LookAt(bool Activate);
	UPROPERTY(BlueprintReadOnly)
	FRotator Rotation;
	UPROPERTY(EditAnywhere)
		float LookAtSpeed = 3.f;
	UPROPERTY(EditAnywhere)
		float TurnAmount = 70.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		EAnimations CurrentAnimation = EAnimations::Idle;
	void ResetLocationVectors();
};
