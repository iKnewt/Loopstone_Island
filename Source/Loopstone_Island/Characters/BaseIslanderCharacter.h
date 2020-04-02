// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PaperFlipBookComponent.h"
#include "GameStateEnums.h"
#include "BaseIslanderCharacter.generated.h"


UENUM(BlueprintType)
enum class EMouthExpression : uint8
{
	Mouth_Talk,
	Mouth_Smile,
	None
};

UENUM(BlueprintType)
enum class EEyeExpression : uint8
{
	Eye_Blinking,
	Eye_Calm,
	Eye_Content,
	Eye_Happy,
	Eye_Excited,
	Eye_Sigh,
	Eye_Sad,
	Eye_Skeptic,
	Eye_Angry,
	Eye_Shock,
	None
};

UCLASS(Blueprintable)
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

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FString Name = "Islander";
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	UFont* Font;
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDataTable* RichTextStyles;
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDialogue* Dialogue = nullptr;
	// Other things that are specific to an islander??

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIslanderType IslanderType;

	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* LeftEye = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* RightEye = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* Mouth = nullptr;


	UPROPERTY(EditAnywhere)
	TArray<UPaperFlipbook*> EyeExpressions;
	UPROPERTY(EditAnywhere)
	TArray<UPaperFlipbook*> MouthExpressions;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperFlipbook* Blinking = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperFlipbook* OpenEye = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperFlipbook* Mouth_Talk = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperFlipbook* Mouth_Smile = nullptr;

	UFUNCTION(BlueprintCallable)
	void ChangeMouthExpression(EMouthExpression MouthExpression);

	UFUNCTION(BlueprintCallable)
	void ChangeEyeExpression(EEyeExpression RightEyeExpression, EEyeExpression LeftEyeExpression);

	UFUNCTION(BlueprintCallable)
	void ChangeAnimation(EAnimations Animation);
};
