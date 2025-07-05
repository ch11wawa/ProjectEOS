// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/EosTitleWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"
#include "Components/EditableText.h"
#include "Widget/Title/EosTitleCharacterSelectWidget.h"
#include "Kismet/GameplayStatics.h"
#include "EosGameInstance.h"
#include "Components/HorizontalBox.h"
#include "PlayerController/EosBasePlayerController.h"



void UEosTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Start)
	{
		Button_Start->OnClicked.AddDynamic(this, &UEosTitleWidget::OnClickedStart);			
	}

	//if (Button_Select)
	//{
	//	Button_Select->OnClicked.AddDynamic(this, &UEosTitleWidget::OnClickedSelect);
	//}

	/*if (Button_ScrollDown)
	{
		Button_ScrollDown->OnClicked.AddDynamic(this, &UEosTitleWidget::ScrollDown);			
	}

	if (Button_ScrollUp)
	{
		Button_ScrollUp->OnClicked.AddDynamic(this, &UEosTitleWidget::ScrollUp);					
	}*/

	//if (Button_ServerTest)
	//{
	//	Button_ServerTest->OnClicked.AddDynamic(this, &UEosTitleWidget::OnClickedTest);
	//}
}

bool UEosTitleWidget::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) return false;

	//AddCharacterBtn();

	return true;
	
}

void UEosTitleWidget::OnClickedStart()
{
	// 로그인 서버 입장
	if (!EditableText_HostIP->GetText().IsEmpty())
	{
		UEosGameInstance* GameInstance = Cast<UEosGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->SetHostIP(EditableText_HostIP->GetText().ToString());
			FString IP = GameInstance->GetHostIP() + TEXT(":7778");
			GameInstance->MoveLevel(IP);
		}
	}
}

//void UEosTitleWidget::OnClickedSelect()
//{
//	// 닉네임 저장 및 레벨 이동
//	UEosGameInstance* GameInstance = Cast<UEosGameInstance>(GetGameInstance());
//	if (GameInstance)
//	{
//		GameInstance->SetNickName(EditableText_NickName->GetText().ToString());
//
//		FString IP = GameInstance->GetHostIP() + TEXT(":7778");
//		GameInstance->MoveLevel(IP);
//	}

	/*AEosBasePlayerController* PlayerController = Cast<AEosBasePlayerController>(GetOwningPlayer());
	if (PlayerController)
	{
		PlayerController->ClientTravel(TEXT("192.168.0.160:7778"), TRAVEL_Absolute);
		UE_LOG(LogTemp, Error, TEXT("Call ClientTravel!"));

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is Null!"));
	}*/

	//UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("192.168.0.160:7778")), true);


	//UGameplayStatics::OpenLevel(GetWorld(), FName("ThirdPersonMap"));

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Select");

//}

//void UEosTitleWidget::OnClickedTest()
//{
//	UEosGameInstance* GameInstance = Cast<UEosGameInstance>(GetGameInstance());
//	if (GameInstance)
//	{
//		GameInstance->SetNickName(EditableText_NickName->GetText().ToString());
//	}
//
//	UGameplayStatics::OpenLevel(GetWorld(), FName("Raid_LionKnight"), true, "?listen");
//}

// 동적으로 위젯 추가
//void UEosTitleWidget::AddCharacterBtn()
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
//		TCSWInstance->OnCharacterSelected.AddDynamic(this, &UEosTitleWidget::SelectCharacter);
//
//	}
//	
//}

// 캐릭터 선택 버튼 클릭 이벤트
//void UEosTitleWidget::SelectCharacter(const int& CharacterClass)
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
