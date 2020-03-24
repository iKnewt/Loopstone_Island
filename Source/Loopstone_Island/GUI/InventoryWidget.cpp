// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Image.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UInventoryWidget::EditInventoryItem(EItem Item, bool TrueToAddFalseToRemove)
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

void UInventoryWidget::AddItem(EItem Item)
{
	switch(Item)
	{
	case EItem::Knife:
		Image_Knife->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItem::Rope:
		Image_Rope->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItem::Tape:
		Image_Tape->SetVisibility(ESlateVisibility::Visible);
		break;
	case EItem::Key:
		Image_Key->SetVisibility(ESlateVisibility::Visible);
		break;
	default: ;
	}
}

void UInventoryWidget::RemoveItem(EItem Item)
{
	switch (Item)
	{
	case EItem::Knife:
		Image_Knife->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EItem::Rope:
		Image_Rope->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EItem::Tape:
		Image_Tape->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EItem::Key:
		Image_Key->SetVisibility(ESlateVisibility::Hidden);
		break;
	default:;
	}
}
