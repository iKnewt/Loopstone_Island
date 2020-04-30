// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/InteractableObjectBase.h"
#include "InteractableBook.generated.h"

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API AInteractableBook : public AInteractableObjectBase
{
	GENERATED_BODY()

public:
	AInteractableBook();

		/** First person camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FString Name = "Book";
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDataTable* RichTextStyles;
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDialogue* Dialogue = nullptr;

	UFUNCTION(BlueprintCallable)
	void Interact() override;
};
