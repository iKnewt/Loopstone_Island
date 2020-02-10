// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UENUM(BlueprintType)
enum class EItems : uint8
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
		void AddItem(EItems Item);
	
};
