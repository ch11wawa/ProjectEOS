// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPC/EosNPCDialogWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "HUD/EosVillageHUD.h"

void UEosNPCDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox_Next->SetVisibility(ESlateVisibility::Collapsed);
	SizeBox_Yes->SetVisibility(ESlateVisibility::Collapsed);
	SizeBox_No->SetVisibility(ESlateVisibility::Collapsed);

	if (Button_Next)
	{
		Button_Next->OnClicked.AddDynamic(this, &UEosNPCDialogWidget::OnClickedNext);
	}

	if (Button_Yes)
	{
		Button_Yes->OnClicked.AddDynamic(this, &UEosNPCDialogWidget::OnClickedYes);
	}

	if (Button_No)
	{
		Button_No->OnClicked.AddDynamic(this, &UEosNPCDialogWidget::OnClickedNo);
	}
}

void UEosNPCDialogWidget::SetDialogText(const FName NewDialogID)
{
	DialogID = NewDialogID;

	if (DialogID == "None")
	{
		return;
	}

	static const FString ContextString(TEXT("FDialogRow"));

	UDataTable* EosNpcDialogTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Blueprints/DataTables/DT_NPCDialog.DT_NPCDialog"));

	if (FDialogRow* Temp = EosNpcDialogTable->FindRow<FDialogRow>(DialogID, ContextString, true))
	{
		DialogRow = *Temp;
	}

	if (!TextBlock_Name->GetText().EqualTo(FText::FromString(DialogRow.NpcName)))
	{
		TextBlock_Name->SetText(FText::FromString(DialogRow.NpcName));
	}

	// Dialog 내용 표시
	TextBlock_Text->SetText(DialogRow.DialogText);

	// 다음 Dialog가 없으면 End버튼, 있으면 Next버튼
	if (DialogRow.NextID == "None")
	{
		TextBlock_NextText->SetText(FText::FromString("END"));
	}
	else
	{
		TextBlock_NextText->SetText(FText::FromString("NEXT"));
	}

	// yes or no 선택 버튼 표시
	if (DialogRow.bIsChoice)
	{
		SizeBox_Next->SetVisibility(ESlateVisibility::Collapsed);
		SizeBox_Yes->SetVisibility(ESlateVisibility::Visible);
		SizeBox_No->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SizeBox_Next->SetVisibility(ESlateVisibility::Visible);
		SizeBox_Yes->SetVisibility(ESlateVisibility::Collapsed);
		SizeBox_No->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UEosNPCDialogWidget::OnClickedNext()
{
	if (TextBlock_NextText->GetText().EqualTo(FText::FromString("NEXT")))
	{
		SetDialogText(DialogRow.NextID);
	}
	else
	{
		GetVillageHUD()->ShowPlayerHUD();
	}
}

void UEosNPCDialogWidget::OnClickedYes()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DialogRow.NextID.ToString());
	SetDialogText(DialogRow.NextID);
}

void UEosNPCDialogWidget::OnClickedNo()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "No");
	SetDialogText(DialogRow.NextID);
}
