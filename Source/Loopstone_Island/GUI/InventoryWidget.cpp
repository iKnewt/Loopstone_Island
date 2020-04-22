// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include <string>
// #include "IDetailTreeNode.h"


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
}

void UInventoryWidget::SetCarrotCounter(int NewAmount)
{
	if (NewAmount == 0)
	{
		CarrotCounter->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		CarrotCounter->SetVisibility(ESlateVisibility::Visible);
		CarrotCounter->SetText(FText::FromString(FString::FromInt(NewAmount)));
	}
}
