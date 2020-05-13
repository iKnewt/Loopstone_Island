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

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AIslandBorder> BorderRef;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WaveDistance = 200;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USoundBase* WoodFootstep;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* GrassFootstep;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* DirtFootstep;

	float SumOfDistance = 0;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DistanceBetweenSteps = 1000000;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 200;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RunSpeed = 500;



	AIslandBorder* Border = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles moving forward/backward with a controller */
	void ControllerMoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/** Handles moving forward/backward with a controller */
	void ControllerMoveRight(float Val);

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
	/**
	 * Called when the player presses the Interact button with a controller.
	 */
	void ControllerInteract();

	bool InteractWithIslander(FHitResult Hit);

	bool InteractWithObject(FHitResult Hit);
	//Holds the reference on the object currently highlighted.
	class AInteractableObjectBase* HighlightedObject = nullptr;

	/**
	 * Does a lineTrace and returns the hit-result.
	 */
	FHitResult RayTrace(float TraceLength, FVector Direction, bool bVisualized = false);

	/**
	 * Plays the footstep sound based on physical material you're walking on
	 */
	void PlayFootstepSoundEffect();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};
