// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PaperFlipBookComponent.h"
#include "BaseIslanderCharacter.generated.h"

UENUM(BlueprintType)
enum class EIslanderType : uint8
{
	Sboi,
	Child,
	Mother,
	Farmer,
	Innkeeper,
	Doctor
};

UENUM(BlueprintType)
enum class EMouthExpression : uint8
{
	Mouth_Talk,
	Mouth_Smile
};

UENUM(BlueprintType)
enum class EEyeExpression : uint8
{
	Eye_Open,
	Eye_Blinking
};

UCLASS()
class LOOPSTONE_ISLAND_API ABaseIslanderCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ABaseIslanderCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIslanderType IslanderType;

	UFUNCTION(BlueprintCallable)
	void ChangeMouthExpression(EMouthExpression MouthExpression);

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* LeftEye = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* RightEye = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* Mouth = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperFlipbook* Blinking = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperFlipbook* OpenEye = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UPaperFlipbook* Mouth_Talk = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UPaperFlipbook* Mouth_Smile = nullptr;

	UFUNCTION(BlueprintCallable)
	void ChangeEyeExpression(EEyeExpression RightEyeExpression, EEyeExpression LeftEyeExpression);
};