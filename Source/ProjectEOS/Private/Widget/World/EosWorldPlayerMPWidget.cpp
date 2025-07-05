// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosWorldPlayerMPWidget.h"
#include "Widget/World/EosWorldBaseProgressBarWidget.h"
#include "AbilitySystem/EosAttributeSet.h"
#include "CoreSystem/PlayerState/EosBasePlayerState.h"

void UEosWorldPlayerMPWidget::UpdateMana(const float& InNewPercent)
{
	ProgressBar_MP->SetColor(FLinearColor::FLinearColor(0.0f, 0.485f, 0.485f));
	ProgressBar_MP->UpdateBar(InNewPercent);
}

void UEosWorldPlayerMPWidget::UpdateStamina(const float& InNewPercent)
{
	ProgressBar_MP->SetColor(FLinearColor::FLinearColor(0.485f, 0.485f, 0.0f));
	ProgressBar_MP->UpdateBar(InNewPercent);
}
