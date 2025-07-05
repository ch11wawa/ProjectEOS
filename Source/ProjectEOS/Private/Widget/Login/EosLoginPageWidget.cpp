// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Login/EosLoginPageWidget.h"
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
#include "HUD/EosLoginHUD.h"


void UEosLoginPageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//if (Button_Login)
	//{
	//	Button_Login->OnClicked.AddDynamic(this, &UEosLoginPageWidget::OnClickedLogin);
	//}
}

void UEosLoginPageWidget::OnClickedLogin()
{
	if (EosGameInstance)
	{
		EosGameInstance->SetPlayerGuid(GUID);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, GUID.ToString());
	}
	GetLoginHUD()->SwitchToCharacterSelection();
	//GetLoginHUD()->SwitchToCreateCharacter();
}

//void UEosLoginPageWidget::Init()
//{
//	TextBlock_Message->SetText(FText::GetEmpty());
//	EditableText_LoginID->SetText(FText::GetEmpty());
//	EditableText_LoginPassword->SetText(FText::GetEmpty());
//	EditableText_NickName->SetText(FText::GetEmpty());
//}

//void UEosLoginPageWidget::OnClickedLogin()
//{
//// 로그인 요청
//
//	// 로그인 성공 시 이동
//	//WidgetSwitcher_LoginPage->SetActiveWidgetIndex(1);
//
//}
//
//void UEosLoginPageWidget::OnClickedSelect()
//{
//	UEosGameInstance* GameInstance = Cast<UEosGameInstance>(GetGameInstance());
//	if (GameInstance)
//	{
//		GameInstance->SetNickName(EditableText_NickName->GetText().ToString());
//
//		FString IP = GameInstance->GetHostIP() + TEXT(":7779");
//		GameInstance->MoveLevel(IP);
//	}
//}
//
//void UEosLoginPageWidget::AddCharacterBtn()
//{
//	if (!TCSWClass) return;
//
//	// Create Widget
//	for (int i = 0; i < CharacterImages.Num(); i++)
//	{
//		TCSWInstance = CreateWidget<UEosTitleCharacterSelectWidget>(this, TCSWClass);
//		if (!TCSWInstance) return;
//
//		if (!CharacterImages.IsValidIndex(i)) continue;
//
//		TCSWInstance->ChangeImage(i, CharacterImages[i]);
//
//		HorizontalBox_CharacterBox->AddChild(TCSWInstance);
//		CharacterButtons.Add(TCSWInstance);
////		TCSWInstance->OnCharacterSelected.AddDynamic(this, &UEosLoginPageWidget::SelectCharacter);
//
//	}
//}
//
//void UEosLoginPageWidget::SelectCharacter(const int& CharacterClass)
//{
//	if (SelectCharacterClass != CharacterClass)
//	{
//		if (SelectCharacterClass >= 0 && SelectCharacterClass < CharacterButtons.Num())
//		{
//			CharacterButtons[SelectCharacterClass]->CancleSelect();
//		}
//		SelectCharacterClass = CharacterClass;
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%d"), SelectCharacterClass));
//
//		// 캐릭터 정보 넘기기
//		UEosGameInstance* GameInstance = Cast<UEosGameInstance>(GetGameInstance());
//		if (GameInstance)
//		{
//			GameInstance->SetPlayerClass(CharacterClass);
//		}
//	}
//}


