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

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Timeline")
	bool bOpenInwards = false;

	UFUNCTION(BlueprintCallable)
	void Interact() override;

	void DoNotInteract() override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	FTimerHandle DoorTimer;

	bool bOpened = false;

	UPROPERTY(EditAnywhere, Category= "Timeline")
	UCurveFloat* CurveFloat;
	//door offset = 43

	UFUNCTION()
	void CloseDoorSound();

	UFUNCTION()
	void PlayAnimation();
	UFUNCTION()
	void UpdateAnimation(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* DoorOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* DoorClose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* DoorLocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* DoorSlam;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
