// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "InventoryWidget.generated.h"

class UImage;
UENUM(BlueprintType)
enum class EItem : uint8
{
	Knife,
	Rope,
	Tape
};

/**
 * 
 */
UCLASS()
class LOOPSTONE_ISLAND_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
		
	UFUNCTION(BlueprintCallable)
	void AddItem(EItem Item);
	UPROPERTY(meta = (BindWidget))
	UImage* Image_Tape;

	UPROPERTY(meta = (BindWidget))
		UImage* Image_Rope;

	UPROPERTY(meta = (BindWidget))
		UImage* Image_Knife;

	
};
