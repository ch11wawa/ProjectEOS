// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosWorldPlayerHPWidget.h"
#include "Widget/World/EosWorldBaseProgressBarWidget.h"
#include "AbilitySystem/EosAttributeSet.h"


void UEosWorldPlayerHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetTimerManager().SetTimer(GetAttributeSetTimer, this, &UEosWorldPlayerHPWidget::GetAttributeSet, 5.0f, false);

}

void UEosWorldPlayerHPWidget::UpdateHP(const float& InNewPercent)
{
	ProgressBar_HP->UpdateBar(InNewPercent);
}

void UEosWorldPlayerHPWidget::GetAttributeSet()
{
	UEosAttributeSet* AttributeSet = GetEosAttributeSet();

	ProgressBar_HP->SetColor(FLinearColor::FLinearColor(0.485f, 0.0f, 0.0f));
	UpdateHP(AttributeSet->GetCurrentHealth() / AttributeSet->GetMaxHealth());
}
