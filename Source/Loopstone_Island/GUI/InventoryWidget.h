// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Condition.h"

#include "InventoryWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void EditInventoryItem(EInventoryItem Item, bool TrueToAddFalseToRemove);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* ItemSound;

private:

	UFUNCTION(BlueprintCallable)
	void AddItem(EInventoryItem Item);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(EInventoryItem Item);

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Tape;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Rope;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Knife;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Key;
};
