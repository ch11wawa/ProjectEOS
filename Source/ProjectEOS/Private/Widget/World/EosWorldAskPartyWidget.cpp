// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosWorldAskPartyWidget.h"
#include "PlayerController/EosWorldPlayerController.h"
#include "Components/TextBlock.h"

UEosWorldAskPartyWidget::UEosWorldAskPartyWidget()
{
	Owner = Cast<AEosWorldPlayerController>(GetOwningPlayer());
}

void UEosWorldAskPartyWidget::AnswerParty(const FGuid HostGUID, const FString& HostNickName)
{
	HostGuid = HostGUID;
	TextBlock_HostNickName->SetText(FText::FromString(HostNickName));
}

void UEosWorldAskPartyWidget::OnClick_Accept()
{
	Owner = Cast<AEosWorldPlayerController>(GetOwningPlayer());

	if (Owner)
	{
		Owner->Client_AnswerParty(HostGuid, true);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "No Owner");

	RemoveFromParent();
}

void UEosWorldAskPartyWidget::OnClick_Decline()
{
	Owner = Cast<AEosWorldPlayerController>(GetOwningPlayer());

	Owner->Client_AnswerParty(HostGuid, false);
	RemoveFromParent();
}
