// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/EosBaseAccountPageWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "HUD/EosLoginHUD.h"
#include "EosGameInstance.h"

void UEosBaseAccountPageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EosGameInstance = Cast<UEosGameInstance>(GetGameInstance());

	Init();
}

void UEosBaseAccountPageWidget::Init()
{
	TextBlock_Message->SetText(FText::GetEmpty());
	EditableText_ID->SetText(FText::GetEmpty());
	EditableText_Password->SetText(FText::GetEmpty());
}

void UEosBaseAccountPageWidget::SetMessage(const FText InMessage)
{
	TextBlock_Message->SetText(InMessage);
}

void UEosBaseAccountPageWidget::OnClickedLogin()
{
}



