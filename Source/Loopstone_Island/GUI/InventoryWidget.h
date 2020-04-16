// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Condition.h"

#include "Components/HorizontalBox.h"

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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AddItemToInventoryWidget(EInventoryItem Item, UTexture2D* Icon);

private:

	UFUNCTION(BlueprintCallable)
	void AddItem(EInventoryItem Item);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(EInventoryItem Item);

	UPROPERTY()
	TArray<UImage*> Images;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_InventoryItems;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HorizontalBox_Items_1;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_0;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_1;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_2;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_3;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_4;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_5;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_6;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_7;
	UPROPERTY(meta = (BindWidget))
	UImage* Image_8;
};
