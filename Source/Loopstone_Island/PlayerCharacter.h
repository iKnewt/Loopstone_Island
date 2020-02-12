// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


UCLASS(Blueprintable)
class LOOPSTONE_ISLAND_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// UPROPERTY()
	// class UHeadBobCameraShake* HeadBobCameraShake;
	//
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> HeadBobWalk;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> HeadBobRun;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY()
	class ALoopstone_IslandGameState* GameState = nullptr;

	UPROPERTY()
	float WalkSpeed = 200;
	UPROPERTY()
	float RunSpeed = 500;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);


	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/**
	* Called via input
	*/
	void Run();

	/**
	* Called via input
	*/
	void StopRunning();

	/**
	 * Called when the player presses the Interact button.
	 */
	void Interact();

	bool InteractWithIslander(FHitResult Hit);

	bool InteractWithObject(FHitResult Hit);

	//Holds the reference on the object currently highlighted.
	class AInteractableObjectBase* HighlightedObject = nullptr;

	/**
	 * Does a lineTrace and returns the hit-result.
	 */
	FHitResult RayTrace(float TraceLength, bool bVisualized = false);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
