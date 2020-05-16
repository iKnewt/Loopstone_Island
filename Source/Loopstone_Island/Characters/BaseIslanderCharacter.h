// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
class UPaperFlipbookComponent;
class UPaperFlipbook;
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
	//~=============================================================================
	// Islander-Specific variables
	// Used for Dialogue System
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FString Name = "Islander";
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UFont* Font;
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDataTable* RichTextStyles;
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDialogue* Dialogue = nullptr;
	UPROPERTY(BlueprintReadWrite)
	bool bLookAtPlayer = true;

	//~=============================================================================
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EIslanderType IslanderType;

	//Expression Components
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* LeftEye = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* RightEye = nullptr;
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* Mouth = nullptr;
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* LookAtCollision;

	UPROPERTY(EditAnywhere)
	TArray<UPaperFlipbook*> EyeExpressions;
	UPROPERTY(EditAnywhere)
	TArray<UPaperFlipbook*> MouthExpressions;

	UFUNCTION(BlueprintCallable)
	void ChangeMouthExpression(EMouthExpression MouthExpression);

	UFUNCTION(BlueprintCallable)
	void ChangeEyeExpression(EEyeExpression RightEyeExpression, EEyeExpression LeftEyeExpression);

	void ChangeAnimation(EAnimations Animation);

	//Snaps the view of the character to front
	void ResetView();
	
	UFUNCTION()
	void OnLookAtBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                          int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnLookAtEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
