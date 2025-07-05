// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/EosCharacterSelectionPageWidget.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "Widget/Login/EosCharacterSlotWidget.h"
#include "Components/SizeBox.h"
#include "EosGameInstance.h"

void UEosCharacterSelectionPageWidget::AddCharacterSlots()
{
	if (!CharacterSlotClass) return;

	// Create Widget
	for (int i = 0; i < CharacterBoxs.Num(); i++)
	{
		CharacterSlotInstance = CreateWidget<UEosCharacterSlotWidget>(this, CharacterSlotClass);
		if (!CharacterSlotInstance) return;

		CharacterSlotInstance->ChangeImage(i, CharacterImages[0]);
		CharacterBoxs[i]->AddChild(CharacterSlotInstance);
		CharacterSlots.Add(CharacterSlotInstance);
		CharacterSlotInstance->SetSlotID(-1);
		CharacterSlotInstance->SetCharacterClass(EPlayerClassType::Empty);
		CharacterSlotInstance->OnCharacterSelected.AddDynamic(this, &UEosBaseSelectionPageWidget::SelectCharacter);
	}
}

EPlayerClassType UEosCharacterSelectionPageWidget::StringToECharacterClass(const FString InString)
{
	UEnum* EnumPtr = StaticEnum<EPlayerClassType>();
	if (EnumPtr)
	{
		int32 Value = EnumPtr->GetValueByName(FName(*InString));
		if (Value != INDEX_NONE)
		{
			return static_cast<EPlayerClassType>(Value);
		}
	}
	return EPlayerClassType::Empty;
}

void UEosCharacterSelectionPageWidget::UpdateCharacterSlots()
{
	if (!CharacterSlotClass) return;

	// Create Widget
	for (int i = 0; i < CharacterClass.Num(); i++)
	{
		if (CharacterSlots.Num() == 0) return;

		CharacterSlots[i]->SetCharacterClass(CharacterClass[i]);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%d"), CharacterClass[i]));

		CharacterSlots[i]->ChangeImage(i, CharacterImages[static_cast<int>(CharacterClass[i])]);
		CharacterSlots[i]->SetSlotID(i);

		CharacterSlots[i]->ShowNickname();
		CharacterSlots[i]->SetTextBlockNickname(NicknameArr[i]);
		CharacterSlots[i]->SetCID(CidArr[i]);
	}
}

void UEosCharacterSelectionPageWidget::OnClickedSelect()
{
	SaveCharacterData();

	Super::OnClickedSelect();
}
