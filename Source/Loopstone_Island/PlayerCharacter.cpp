// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InteractableObjectBase.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "CookStats.h"
#include "BaseIslanderCharacter.h"
#include "Loopstone_IslandGameState.h"
#include "IslandBorder.h"
#include "Components/AudioComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(30.f, 60.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// setup default settings for movement
	GetCharacterMovement()->MaxStepHeight = 10.f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->JumpZVelocity = 300;
	GetCharacterMovement()->AirControl = 0.4f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(BorderRef))
	{
		AActor* Actor = GetWorld()->SpawnActor(BorderRef);
		Border = dynamic_cast<AIslandBorder*>(Actor);
		if(!IsValid(Border))
		{
			UE_LOG(LogTemp, Error, TEXT("BORDER NOT INITALIZED"));
		}
	}


	

	GameState = dynamic_cast<ALoopstone_IslandGameState*>(GetWorld()->GetGameState());
	if (!GameState)
	{
		UE_LOG(LogTemp, Error, TEXT("CORRECT GAME STATE NOT FOUND"));
	}
	else
	{
		GameState->Player = this;
	}
}

void APlayerCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Val);
	}

	//	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(MyShake, 1.0f);
}

void APlayerCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APlayerCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO This should be done better. bit too many checks rn

	FHitResult Hit = RayTrace(400);
	if (Hit.bBlockingHit)
	{
		if (Hit.Actor->ActorHasTag("Interact"))
		{
			AInteractableObjectBase* Object = Cast<AInteractableObjectBase>(Hit.Actor);
			if (Object)
			{
				if (HighlightedObject)
				{
					if (Object->GetUniqueID() != HighlightedObject->GetUniqueID())
					{
						HighlightedObject->VisualizeInteraction(false);
					}
				}
				if (!Object->bVisualizingInteraction)
				{
					Object->VisualizeInteraction(true);
					HighlightedObject = Object;
				}
			}
		}
		else if (HighlightedObject != nullptr)
		{
			HighlightedObject->VisualizeInteraction(false);
			HighlightedObject = nullptr;
		}
	}
	else if (HighlightedObject != nullptr)
	{
		HighlightedObject->VisualizeInteraction(false);
		HighlightedObject = nullptr;
	}

	// GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(HeadBobCameraShake, 1.0f);

	//TODO this could perhaps be on whenever the user moves? just as a way to get as little as possible on tick.

	if (GetVelocity().Size() > 0 && CanJump())
	{
		//	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(MyShake, 1.0f);

		if (GetVelocity().Size() < 300)
		{
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HeadBobWalk);
		}
		else
		{
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HeadBobRun);
		}
	}

	if(IsValid(Border))
	{
		FVector PointClosestToPlayer = Border->Spline->FindLocationClosestToWorldLocation(GetActorLocation(), ESplineCoordinateSpace::World);
		float Distance = PointClosestToPlayer.Size();

		if(Distance < WaveDistance)
		{
			if(!Border->Waves->IsPlaying())
			{
				Border->Waves->Play();
			}
			Border->Waves->SetVolumeMultiplier(1 - Distance / WaveDistance);
		
		}
		else
		{
			if(Border->Waves->IsPlaying())
			{
				Border->Waves->Stop();
			}
		}
		
		
	}
	
}

bool APlayerCharacter::InteractWithIslander(FHitResult Hit)
{
	ABaseIslanderCharacter* Islander = Cast<ABaseIslanderCharacter>(Hit.Actor);
	if (Islander && GameState)
	{
		GameState->StartDialogue(Islander);
		return true;
	}
	return false;
}

bool APlayerCharacter::InteractWithObject(FHitResult Hit)
{
	AInteractableObjectBase* InteractableObject = Cast<AInteractableObjectBase>(Hit.Actor);
	if (InteractableObject)
	{
		GameState->InteractWithObject(InteractableObject);
		return true;
	}
	return false;
}

void APlayerCharacter::Interact()
{
	FHitResult Hit = RayTrace(400);

	if (Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact Hit: %s"), *GetDebugName(Hit.GetActor()));
		if (InteractWithObject(Hit))
		{
			return;
		}
		if (InteractWithIslander(Hit))
		{
			return;
		}
		UE_LOG(LogTemp, Error, TEXT("Interact Hit: Object not interactable"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact Hit: Hit Nothing"));
	}
}

FHitResult APlayerCharacter::RayTrace(float TraceLength, bool bVisualized)
{
	FHitResult Hit(ForceInit);
	FVector Start = FirstPersonCameraComponent->GetComponentLocation() +
		FirstPersonCameraComponent->GetForwardVector() * 50;
	FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * 400.f;
	FCollisionQueryParams collisionParam;
	GetWorld()->LineTraceSingleByChannel(
		Hit, Start, End, ECC_WorldDynamic, collisionParam);
	if (bVisualized)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	}
	return Hit;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Bind Interact event
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

	// Bind Run events
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRunning);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);


	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}
