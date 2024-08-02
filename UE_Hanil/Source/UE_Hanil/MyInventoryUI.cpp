// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UMyInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();

	auto array = SlotGrid->GetAllChildren();

	for (auto widget : array)
	{
		auto btn = Cast<UButton>(widget);
		if (btn)
		{
			_slotBtns.Add(btn);
			_slotBtnImages.Add(Cast<UImage>(btn->GetChildAt(0)));
		}
	}

	_axe = LoadObject<UTexture2D>(nullptr,TEXT("/Script/Engine.Texture2D'/Game/Graphics/Icons/Tex_tools_01.Tex_tools_01'"));
	_defalut = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphics/Icons/Tex_Default.Tex_Default'"));
}

void UMyInventoryUI::SetItem(int32 itemId, int32 index)
{
	if(_slotBtnImages.IsEmpty() || !_slotBtnImages.IsValidIndex(index))
		return;

	if (itemId == -1)
	{
		_slotBtnImages[index]->SetBrushFromTexture(_defalut);
	}
	else if (itemId == 1)
	{
		_slotBtnImages[index]->SetBrushFromTexture(_axe);
	}
	else
		return;
}
