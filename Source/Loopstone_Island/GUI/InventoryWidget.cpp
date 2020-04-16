// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Image.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "IDetailTreeNode.h"


void UInventoryWidget::EditInventoryItem(EInventoryItem Item, bool TrueToAddFalseToRemove)
{
	if (Images.Num() == 0)
	{
		Images.Add(Image_0);
		Images.Add(Image_1);
		Images.Add(Image_2);
		Images.Add(Image_3);
		Images.Add(Image_4);
		Images.Add(Image_5);
		Images.Add(Image_6);
		Images.Add(Image_7);
		Images.Add(Image_8);


		for (auto image : Images)
		{
			image->SetVisibility(ESlateVisibility::Collapsed);
		}		
	}

	int index = static_cast<int>(Item);
	if (index < Images.Num())
	{
		if (TrueToAddFalseToRemove)
		{
			Images[index]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Images[index]->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (ItemSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ItemSound);
		}
	}

	
	//
	// if (TrueToAddFalseToRemove)
	// {
	// 	AddItem(Item);
	// }
	// else
	// {
	// 	RemoveItem(Item);
	// }
}

void UInventoryWidget::AddItem(EInventoryItem Item)
{
	// HorizontalBox_Items->AddChildToHorizontalBox(new UWidget(FObjectInitializer()));

	// auto test = new UImage()


	// UMG_API::CreateWidget(this, UImage*, FName("skdjh"));

	// auto test = UMG_API::CreateWidget(this);
	//
	// auto test2 = UMG_API::CreateWidget(this);


	// UImage::

	// HorizontalBox_Items->AddChildToHorizontalBox(Image_Knife);
	// HorizontalBox_Items->AddChild()

	// switch(Item)
	// {
	// case EInventoryItem::Knife:
	// 	Image_Knife->SetVisibility(ESlateVisibility::Visible);
	// 	// Image_Knife->SetBrushFromTexture(UTexture2D)
	// 	break;
	// case EInventoryItem::Rope:
	// 	Image_Rope->SetVisibility(ESlateVisibility::Visible);
	// 	break;
	// case EInventoryItem::Tape:
	// 	Image_Tape->SetVisibility(ESlateVisibility::Visible);
	// 	break;
	// case EInventoryItem::Key:
	// 	Image_Key->SetVisibility(ESlateVisibility::Visible);
	// 	break;
	// default: ;
	// }
}

void UInventoryWidget::RemoveItem(EInventoryItem Item)
{
	// switch (Item)
	// {
	// case EInventoryItem::Knife:
	// 	Image_Knife->SetVisibility(ESlateVisibility::Hidden);
	// 	break;
	// case EInventoryItem::Rope:
	// 	Image_Rope->SetVisibility(ESlateVisibility::Hidden);
	// 	break;
	// case EInventoryItem::Tape:
	// 	Image_Tape->SetVisibility(ESlateVisibility::Hidden);
	// 	break;
	// case EInventoryItem::Key:
	// 	Image_Key->SetVisibility(ESlateVisibility::Hidden);
	// 	break;
	// default:;
	// }
}
