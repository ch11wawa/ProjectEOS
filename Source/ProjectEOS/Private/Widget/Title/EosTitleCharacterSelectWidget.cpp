// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/EosTitleCharacterSelectWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "EosGameInstance.h"


bool UEosTitleCharacterSelectWidget::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) 	return false;

	if (Button_Character)
	{
		Button_Character->OnClicked.AddDynamic(this, &UEosTitleCharacterSelectWidget::OnClickedCharacter);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}

	return true;
}

void UEosTitleCharacterSelectWidget::OnClickedCharacter()
{
	SizeBox_Select->SetVisibility(ESlateVisibility::Visible);
	//OnCharacterSelected.Broadcast(CharacterClass);
}

// 이미지 변경 함수
void UEosTitleCharacterSelectWidget::ChangeImage(int Index, UTexture2D* NewImage)
{
	CharacterClass = Index;
	if(Image_CharacterImage)
		Image_CharacterImage->SetBrushFromTexture(NewImage);
}

void UEosTitleCharacterSelectWidget::CancleSelect()
{
	SizeBox_Select->SetVisibility(ESlateVisibility::Hidden);
}
