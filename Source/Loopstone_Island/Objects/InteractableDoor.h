// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "InteractableObjectBase.h"
#include "InteractableDoor.generated.h"


class UCurveFloat;

UCLASS()
class LOOPSTONE_ISLAND_API AInteractableDoor : public AInteractableObjectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableDoor();
	
	UFUNCTION(BlueprintCallable)
	void Interact() override;

	void DoNotInteract() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//~=============================================================================
	// Timeline variables	
	FTimeline CurveTimeline;
	FTimerHandle DoorTimer;
	UPROPERTY(EditAnywhere, Category= "Timeline")
	UCurveFloat* CurveFloat;

	UFUNCTION()
	void CloseDoorSound();

	UFUNCTION()
	void PlayAnimation();
	UFUNCTION()
	void UpdateAnimation(float Value);


	//~=============================================================================
	// Sounds	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* DoorOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* DoorClose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* DoorLocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* DoorSlam;

	//~=============================================================================
	// Door Variables	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		bool bOpenInwards = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
		bool bDoorLockedOnBeginPlay = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lock")
		bool bDoorAlwaysLocked = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		bool bAutoClose = true;
	// If the door is currently open = true
	bool bOpen = false;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
