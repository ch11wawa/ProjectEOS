// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/EosCharacterSlotWidget.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "EosGameInstance.h"


bool UEosCharacterSlotWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) 	return false;

	if (Button_Character)
	{
		Button_Character->OnClicked.AddDynamic(this, &UEosCharacterSlotWidget::OnClickedCharacter);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}

	CharacterClass = EPlayerClassType::Empty;

	return true;
}

void UEosCharacterSlotWidget::OnClickedCharacter()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "OnClickedCharacter");
	SizeBox_Select->SetVisibility(ESlateVisibility::Visible);
	OnCharacterSelected.Broadcast(SlotID);
}

// 이미지 변경 함수
void UEosCharacterSlotWidget::ChangeImage(int Index, UTexture2D* NewImage)
{
	//UEnum* EnumPtr = StaticEnum<EPlayerClassType>();
	//if (EnumPtr && EnumPtr->IsValidEnumValue(Index))
	//{
	//	EPlayerClassType Result = static_cast<EPlayerClassType>(Index);
	//}

	if (Image_CharacterImage)
		Image_CharacterImage->SetBrushFromTexture(NewImage);
}

void UEosCharacterSlotWidget::SetTextBlockNickname(const FString NewNickname)
{
	TextBlock_Nickname->SetText(FText::FromString(NewNickname));
	Nickname = NewNickname;
}

void UEosCharacterSlotWidget::CancleSelect()
{
	SizeBox_Select->SetVisibility(ESlateVisibility::Hidden);
}

void UEosCharacterSlotWidget::ShowNickname()
{
	SizeBox_Nickname->SetVisibility(ESlateVisibility::Visible);
}




