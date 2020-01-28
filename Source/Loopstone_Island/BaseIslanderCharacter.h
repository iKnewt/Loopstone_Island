// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	Mouth_Expression_00,
	Mouth_Expression_01,
	Mouth_Expression_02,
	Mouth_Expression_03,
	Mouth_Expression_04,
	Mouth_Expression_05,
	Mouth_Expression_06,
	Mouth_Expression_07,
	Mouth_Expression_08,
	Mouth_Expression_09,
	Mouth_Expression_10,
	Mouth_Expression_11,
	Mouth_Expression_12,
	Mouth_Expression_13,
	Mouth_Expression_14,
	Mouth_Expression_15,
	Mouth_Expression_16,
	Mouth_Expression_17,
	Mouth_Expression_18,
	Mouth_Expression_19
};

UENUM(BlueprintType)
enum class EEyeExpression : uint8
{
	Eye_Expression_00,
	Eye_Expression_01,
	Eye_Expression_02,
	Eye_Expression_03,
	Eye_Expression_04,
	Eye_Expression_05,
	Eye_Expression_06,
	Eye_Expression_07,
	Eye_Expression_08,
	Eye_Expression_09,
	Eye_Expression_10,
	Eye_Expression_11,
	Eye_Expression_12,
	Eye_Expression_13,
	Eye_Expression_14,
	Eye_Expression_15,
	Eye_Expression_16,
	Eye_Expression_17,
	Eye_Expression_18,
	Eye_Expression_19
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

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* EyePlate = nullptr;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* MouthPlate = nullptr;


	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* EyePlateMaterial = nullptr;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* MouthPlateMaterial = nullptr;

	UFUNCTION(BlueprintCallable)
	void ChangeMouthExpression(EMouthExpression MouthExpression);

	UFUNCTION(BlueprintCallable)
	void ChangeEyeExpression(EEyeExpression EyeExpression);

	void CreateDynamicFaceMaterials();
};
