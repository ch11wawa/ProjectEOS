// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/EosLoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/Title/EosTitleCharacterSelectWidget.h"
#include "EosGameInstance.h"
#include "Widget/Login/EosSignupPageWidget.h"
#include "Widget/Login/EosLoginPageWidget.h"



void UEosLoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_LoginPage)
	{
		Button_LoginPage->OnClicked.AddDynamic(this, &UEosLoginWidget::OnClickedLoginPage);
	}

	if (Button_SignupPage)
	{
		Button_SignupPage->OnClicked.AddDynamic(this, &UEosLoginWidget::OnClickedSignupPage);
	}

	//if (Button_Login)
	//{
	//	Button_Login->OnClicked.AddDynamic(this, &UEosLoginWidget::OnClickedLogin);
	//}

	////if (Button_Signup)
	////{
	////	Button_Signup->OnClicked.AddDynamic(this, &UEosLoginWidget::OnClickedSignup);
	////}

	if (Button_Back)
	{
		Button_Back->OnClicked.AddDynamic(this, &UEosLoginWidget::OnClickedBack);
	}

	////if (Button_SignupBack)
	////{
	////	Button_SignupBack->OnClicked.AddDynamic(this, &UEosLoginWidget::OnClickedBack);
	////}

	//if (Button_Select)
	//{
	//	Button_Select->OnClicked.AddDynamic(this, &UEosLoginWidget::OnClickedSelect);
	//}
}

bool UEosLoginWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

//	AddCharacterBtn();
	Init();
	return true;
}

void UEosLoginWidget::Init()
{
	Button_Back->SetVisibility(ESlateVisibility::Collapsed);
	SignupPageWidget->Init();
	LoginPageWidget->Init();
}

void UEosLoginWidget::OnClickedLoginPage()
{
	WidgetSwitcher_Account->SetActiveWidgetIndex(1);
	Button_Back->SetVisibility(ESlateVisibility::Visible);
}

void UEosLoginWidget::OnClickedSignupPage()
{
	WidgetSwitcher_Account->SetActiveWidgetIndex(2);
	Button_Back->SetVisibility(ESlateVisibility::Visible);

}

void UEosLoginWidget::OnClickedBack()
{
	Init();
	WidgetSwitcher_Account->SetActiveWidgetIndex(0);
}