// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosWorldPlayerHudWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/SizeBox.h"
#include "Widget/World/EosWorldPartyWidget.h"
#include "Widget/World/EosWorldAskPartyWidget.h"
#include "Widget/World/EosBossWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Enums/EosEnumTypes.h"

UEosWorldPlayerHudWidget::UEosWorldPlayerHudWidget()
{
}

void UEosWorldPlayerHudWidget::SwitchMenu(EMenuStatus InMenuStatus)
{
	switch (InMenuStatus)
	{
	case EMenuStatus::Main:
		WidgetSwitcher->SetActiveWidgetIndex(0);
		break;
	case EMenuStatus::Menu:
		//TODO: Menu구현
		break;
	case EMenuStatus::Inventory:
		WidgetSwitcher->SetActiveWidget(WBP_InventoryMainWidget);
		break;
	case EMenuStatus::Skill:
		//TODO: Skill구현
		WidgetSwitcher->SetActiveWidgetIndex(0);
		break;
	case EMenuStatus::Map:
		//TODO: Map구현
		WidgetSwitcher->SetActiveWidgetIndex(0);
		break;
	default:
		break;
	}
}

void UEosWorldPlayerHudWidget::SetPartyUI(const FPlayerInfo& PlayerInfo)
{
	for (auto& Party : PartyArr)
	{
		if (Party->GetVisibility() == ESlateVisibility::Hidden)
		{
			Party->SetPartyGuid(PlayerInfo.PlayerGUID);
			Party->SetPartyUI(FText::FromString(PlayerInfo.NickName), FaceImageArr[static_cast<int>(PlayerInfo.CharacterClass)]);
			Party->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	}
}

void UEosWorldPlayerHudWidget::UpdatePartyUI(const FGuid TargetGuid, float HP)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Update Party UI");

	for (auto& Party : PartyArr)
	{
		if (Party->GetVisibility() == ESlateVisibility::Visible)
		{
			if (Party->GetPartyGuid() == TargetGuid)
			{
				Party->UpdatePartyHP(HP);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "NoPlayerState");
			}
		}
	}
}

void UEosWorldPlayerHudWidget::PopUpAskParty(const FGuid HostGUID, const FString& HostNickName)
{
	if (!AskPartyClass) return;

	// Create Widget
	AskPartyInstance = CreateWidget<UEosWorldAskPartyWidget>(this, AskPartyClass);
	if (AskPartyInstance)
	{
		AskPartyInstance->AnswerParty(HostGUID, HostNickName);
		SizeBox_AskParty->AddChild(AskPartyInstance);
	}
}

void UEosWorldPlayerHudWidget::ShowBossHP()
{
	if (!BossWidgetClass) return;

	// Create Widget
	BossWidgetInstance = CreateWidget<UEosBossWidget>(this, BossWidgetClass);
	if (BossWidgetInstance)
	{
		SizeBox_BossHp->AddChild(BossWidgetInstance);
	}
}