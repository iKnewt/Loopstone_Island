// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Image.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UInventoryWidget::EditInventoryItem(EInventoryItem Item, bool TrueToAddFalseToRemove)
{
	if(ItemSound)
	{

		
		UGameplayStatics::PlaySound2D(GetWorld(), ItemSound);
		// if(!ItemSound->IsPlaying())
		// {
		// 	ItemSound->Play();
		// }
	}
	
	if(TrueToAddFalseToRemove)
	{
		AddItem(Item);
	}
	else
	{
		RemoveItem(Item);
	}
}

void UInventoryWidget::AddItem(EInventoryItem Item)
{
	switch(Item)
	{
	case EInventoryItem::Knife:
		Image_Knife->SetVisibility(ESlateVisibility::Visible);
		break;
	case EInventoryItem::Rope:
		Image_Rope->SetVisibility(ESlateVisibility::Visible);
		break;
	case EInventoryItem::Tape:
		Image_Tape->SetVisibility(ESlateVisibility::Visible);
		break;
	case EInventoryItem::Key:
		Image_Key->SetVisibility(ESlateVisibility::Visible);
		break;
	default: ;
	}
}

void UInventoryWidget::RemoveItem(EInventoryItem Item)
{
	switch (Item)
	{
	case EInventoryItem::Knife:
		Image_Knife->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EInventoryItem::Rope:
		Image_Rope->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EInventoryItem::Tape:
		Image_Tape->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EInventoryItem::Key:
		Image_Key->SetVisibility(ESlateVisibility::Hidden);
		break;
	default:;
	}
}
