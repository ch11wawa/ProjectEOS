// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/EosSignupPageWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "EosFunctionLibrary.h"
#include "HUD/EosLoginHUD.h"
#include "EosGameInstance.h"

void UEosSignupPageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GUID = FGuid::NewGuid();
	if (EosGameInstance)
	{
		EosGameInstance->SetPlayerGuid(GUID);
	}
	
	Init();
}

void UEosSignupPageWidget::OnClickedLogin()
{
	GetLoginHUD()->SwitchToCreateCharacter();
}

void UEosSignupPageWidget::UsernameDuplicateCheck()
{
	for (auto& Existed : ExistedUsername)
	{
		if (Username.Equals(Existed))
		{
			SetMessage(FText::FromString("This ID already exists."));
			return;
		}
	}

	SetMessage(FText::FromString("You can use this ID."));
	SizeBox_Singup->SetIsEnabled(true);
	SizeBox_IDCheck->SetIsEnabled(false);
	CheckedUsername = Username;
}

bool UEosSignupPageWidget::IsAlphaOrNumber(const FString& InString)
{
	if ((InString[0] < 'A' || InString[0] > 'Z') && (InString[0] < 'a' || InString[0] > 'z')) return false;

	for (auto& Char : InString)
	{
		if((Char < 'A' || Char > 'Z') && (Char < 'a' || Char > 'z') && (Char < '0' || Char > '9'))
			return false;
	}
	return true;
}

bool UEosSignupPageWidget::IsVaildPassword(const FString& InString)
{
	bool bHasAlpha = false, bHasDigit = false;

	for (auto& Char : InString)
	{
		if ((Char < 'A' || Char > 'Z') && (Char < 'a' || Char > 'z') && (Char < '0' || Char > '9'))
			return false;

		if (FChar::IsDigit(Char)) bHasDigit = true;

		if (FChar::IsAlpha(Char)) bHasAlpha = true;
	}

	if (bHasDigit && bHasAlpha) return true;
	return false;
}


void UEosSignupPageWidget::Init()
{
	Super::Init();
	EditableText_ConfirmPassword->SetText(FText::GetEmpty());
	SetMessage(FText::GetEmpty());
	SizeBox_Singup->SetIsEnabled(false);
}
