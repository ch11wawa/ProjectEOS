// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/EosBaseSelectionPageWidget.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "Widget/Login/EosCharacterSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "HUD/EosLoginHUD.h"
#include "EosGameInstance.h"

void UEosBaseSelectionPageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CharacterImages.IsEmpty()) return;

	EosGameInstance = Cast<UEosGameInstance>(GetGameInstance());
	if (EosGameInstance)
	{
		GUID = EosGameInstance->GetPlayerGuid();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, GUID.ToString());
	}

	if (Button_Select)
	{
		Button_Select->OnClicked.AddDynamic(this, &UEosBaseSelectionPageWidget::OnClickedSelect);
	}

	GetCharacterInfoFromDatabase();

	AddCharacterSlots();
}

FString UEosBaseSelectionPageWidget::EnumToString(EPlayerClassType ClassType)
{
	UEnum* EnumPtr = StaticEnum<EPlayerClassType>();
	if (!EnumPtr) return FString("Invalid");

	return EnumPtr->GetNameStringByValue(static_cast<int64>(ClassType));
}

void UEosBaseSelectionPageWidget::OnClickedSelect()
{
	SaveCharacterData();

	if (EosGameInstance)
	{
		FString IP = EosGameInstance->GetHostIP() + TEXT(":7779");
		EosGameInstance->MoveLevel(IP);
	}
}

void UEosBaseSelectionPageWidget::SaveCharacterData()
{
	// 캐릭터 정보 넘기기
	if (EosGameInstance)
	{
		EosGameInstance->SetPlayerClass(SelectedSlot->GetCharacterClass());
		EosGameInstance->SetNickName(Nickname);
		EosGameInstance->SetPlayerGuid(CID);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Yes GameInstance");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "No GameInstance");
	}
}

void UEosBaseSelectionPageWidget::AddCharacterSlots()
{
	if (!CharacterSlotClass) return;

	// Create Widget
	for (int i = 1; i < CharacterImages.Num(); ++i)
	{
		CharacterSlotInstance = CreateWidget<UEosCharacterSlotWidget>(this, CharacterSlotClass);
		if (!CharacterSlotInstance) return;

		if (!CharacterImages.IsValidIndex(i)) continue;

		CharacterSlotInstance->ChangeImage(i, CharacterImages[i]);
		CharacterSlotInstance->SetCharacterClass(static_cast<EPlayerClassType>(i));
		CharacterSlotInstance->SetSlotID(i - 1);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("SlotID : %d"), CharacterSlotInstance->GetSlotID()));

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("Enum : %d"), static_cast<EPlayerClassType>(i)));

		HorizontalBox_SlotBox->AddChild(CharacterSlotInstance);
		CharacterSlots.Add(CharacterSlotInstance);
		CharacterSlotInstance->OnCharacterSelected.AddDynamic(this, &UEosBaseSelectionPageWidget::SelectCharacter);
	}
}

void UEosBaseSelectionPageWidget::SelectCharacter(const int32 SlotID)
{
	if (SlotID == -1)
	{
		Cast<AEosLoginHUD>(GetOwningPlayer()->GetHUD())->SwitchToCreateCharacter();
		return;
	}

	if (!SelectedSlot)
	{
		SelectedSlot = CharacterSlots[SlotID];
	}
	else if (SelectedSlot && SelectedSlot->GetSlotID() != SlotID)
	{
		SelectedSlot->CancleSelect();
		
		SelectedSlot = CharacterSlots[SlotID];
	}

	Nickname = SelectedSlot->GetNickname();
	CID = SelectedSlot->GetCID();
}