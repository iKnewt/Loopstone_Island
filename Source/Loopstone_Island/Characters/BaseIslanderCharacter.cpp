// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseIslanderCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipBookComponent.h"
#include "Components/CapsuleComponent.h" //this is needed, dunno why it says it doesn't (line 30)
#include "Components/SphereComponent.h"
#include "IslanderAnimationInstance.h"
#include "Dialogue/Dialogue.h"

// Sets default values
ABaseIslanderCharacter::ABaseIslanderCharacter()
{
	//No reason for it to tick
	PrimaryActorTick.bCanEverTick = false;

	RightEye = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("RightEye"));
	LeftEye = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("LeftEye"));
	Mouth = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("MouthPlate"));
	RightEye->SetupAttachment(GetMesh(), FName("HeadSocket"));
	LeftEye->SetupAttachment(GetMesh(), FName("HeadSocket"));
	Mouth->SetupAttachment(GetMesh(), FName("HeadSocket"));

	EyeExpressions.SetNum(static_cast<int>(EEyeExpression::None) + 1);
	MouthExpressions.SetNum(static_cast<int>(EMouthExpression::None) + 1);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());

	//Set up Sphere for LookAt-Function
	LookAtCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LookAtSphere"));
	LookAtCollision->SetupAttachment(GetRootComponent());
	LookAtCollision->SetSphereRadius(500);
}

// Called when the game starts or when spawned
void ABaseIslanderCharacter::BeginPlay()
{
	Super::BeginPlay();
	RightEye->PlayFromStart();
	LeftEye->PlayFromStart();
	Mouth->PlayFromStart();

	EyeExpressions.SetNum(static_cast<int>(EEyeExpression::None) + 1);
	MouthExpressions.SetNum(static_cast<int>(EMouthExpression::None) + 1);
	LookAtCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseIslanderCharacter::OnLookAtBeginOverlap);
	LookAtCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseIslanderCharacter::OnLookAtEndOverlap);

	if (Dialogue)
	{
		Dialogue->ResetDialogue();
	}
}

// Called to bind functionality to input

void ABaseIslanderCharacter::ChangeMouthExpression(const EMouthExpression MouthExpression)
{
	// testing arrayed
	UE_LOG(LogTemp, Warning, TEXT("Mouth set to %s"), *UEnum::GetValueAsString(MouthExpression));

	UE_LOG(LogTemp, Warning, TEXT("Mouth %i | Array size %i"), static_cast<int>(MouthExpression),
	       MouthExpressions.Num());

	auto NewMouth = MouthExpressions[static_cast<int>(MouthExpression)];
	if (NewMouth)
	{
		Mouth->SetFlipbook(NewMouth);
		Mouth->PlayFromStart();
	}
}

void ABaseIslanderCharacter::ChangeEyeExpression(EEyeExpression RightEyeExpression, EEyeExpression LeftEyeExpression)
{
	UE_LOG(LogTemp, Warning, TEXT("Right Eye set to %s"), *UEnum::GetValueAsString(RightEyeExpression));
	UE_LOG(LogTemp, Warning, TEXT("Left Eye set to %s"), *UEnum::GetValueAsString(LeftEyeExpression));

	const auto NewRightEye = EyeExpressions[static_cast<int>(RightEyeExpression)];
	if (NewRightEye)
	{
		RightEye->SetFlipbook(NewRightEye);
		RightEye->PlayFromStart();
	}
	const auto NewLeftEye = EyeExpressions[static_cast<int>(LeftEyeExpression)];
	if (NewLeftEye)
	{
		LeftEye->SetFlipbook(NewLeftEye);
		LeftEye->PlayFromStart();
	}
}

void ABaseIslanderCharacter::ChangeAnimation(EAnimations Animation)
{
	UIslanderAnimationInstance* AnimationInstance = Cast<UIslanderAnimationInstance>(GetMesh()->GetAnimInstance());
	if (IsValid(AnimationInstance))
	{
		AnimationInstance->CurrentAnimation = Animation;
	}
}

void ABaseIslanderCharacter::ResetView()
{
	UIslanderAnimationInstance* AnimationInstance = Cast<UIslanderAnimationInstance>(GetMesh()->GetAnimInstance());
	if (IsValid(AnimationInstance))
	{
		AnimationInstance->ResetLocationVectors();
		AnimationInstance->LookAt(false);
	}
}

void ABaseIslanderCharacter::OnLookAtBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                  const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag("Player"))
		{
			UIslanderAnimationInstance* AnimationInstance = Cast<UIslanderAnimationInstance>(
				GetMesh()->GetAnimInstance());
			if (IsValid(AnimationInstance))
			{
				if (bLookAtPlayer)
				{
					AnimationInstance->LookAt(true);
				}
			}
		}
	}
}

void ABaseIslanderCharacter::OnLookAtEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsValid(OtherActor))
	{
		if (OtherActor->ActorHasTag("Player"))
		{
			UIslanderAnimationInstance* AnimationInstance = Cast<UIslanderAnimationInstance>(
				GetMesh()->GetAnimInstance());
			if (IsValid(AnimationInstance))
			{
				AnimationInstance->LookAt(false);
			}
		}
	}
}
