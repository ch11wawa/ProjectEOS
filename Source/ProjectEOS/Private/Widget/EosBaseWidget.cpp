// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/EosBaseWidget.h"
#include "ProjectEOS/Public/Components/Inventory/EosInventoryComponent.h"
#include "Components/WrapBox.h"
#include "ProjectEOS/Public/Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "Components/UI/EosBaseUIComponent.h"
#include "Components/UI/EosPlayerUIComponent.h"
#include "CoreSystem/PlayerState/EosBasePlayerState.h"
#include "HUD/EosLoginHUD.h"
#include "HUD/EosVillageHUD.h"

UEosBaseUIComponent* UEosBaseWidget::BringUIComponent(AActor* Character)
{
	if (Character->GetComponentByClass(UEosBaseUIComponent::StaticClass()))
	{
		UEosBaseUIComponent* UIComponent = Cast<UEosBaseUIComponent>(Character->GetComponentByClass(UEosBaseUIComponent::StaticClass()));

		return UIComponent;
	}
	return nullptr;
}

UEosPlayerUIComponent* UEosBaseWidget::BringPlayerUIComponent()
{
	if (GetOwningPlayerPawn())
	{
		UEosBaseUIComponent* Base = BringUIComponent(GetOwningPlayerPawn());
		if (Base)
		{
			return Cast<UEosPlayerUIComponent>(Base);
		}
	}
	return nullptr;
}

UEosAttributeSet* UEosBaseWidget::GetEosAttributeSet()
{
	if (GetOwningPlayerPawn())
	{
		AEosBasePlayerState* PlayerState = Cast<AEosBasePlayerState>(GetOwningPlayerPawn()->GetPlayerState());

		if(PlayerState)
			return PlayerState->EosAttributeSet;
	}
	return nullptr;
}

AEosLoginHUD* UEosBaseWidget::GetLoginHUD() const
{
	if (GetOwningPlayer()->GetHUD())
	{
		return Cast<AEosLoginHUD>(GetOwningPlayer()->GetHUD());
	}
	return nullptr;
}

AEosVillageHUD* UEosBaseWidget::GetVillageHUD() const
{
	if (GetOwningPlayer()->GetHUD())
	{
		return Cast<AEosVillageHUD>(GetOwningPlayer()->GetHUD());
	}
	return nullptr;
}

AEosBasePlayerCharacter* UEosBaseWidget::GetEosBasePlayerCharacter() const
{
	if (GetOwningPlayerPawn())
	{
		return Cast<AEosBasePlayerCharacter>(GetOwningPlayerPawn());
	}
	return nullptr;
}
