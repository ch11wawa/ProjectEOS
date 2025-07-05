// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosWorldBaseProgressBarWidget.h"
#include "Components/Image.h"

void UEosWorldBaseProgressBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	DynamicMaterial = UMaterialInstanceDynamic::Create(ProgressBarMaterial, this);
	Image_Fill->SetBrushFromMaterial(DynamicMaterial);
}

void UEosWorldBaseProgressBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CurrentAlpha += (InDeltaTime / ResponseTime);

	float value = FMath::InterpEaseOut(PreviousPercent, Percent, FMath::Clamp(CurrentAlpha, 0.0f, 1.0f), 2.0f);

	DynamicMaterial->SetScalarParameterValue("percentage", value);
}

void UEosWorldBaseProgressBarWidget::SetColor(FLinearColor NewColor)
{
	DynamicMaterial->SetVectorParameterValue("Color", NewColor);
}

void UEosWorldBaseProgressBarWidget::UpdateBar(float NewPercent)
{
	PreviousPercent = Percent;
	Percent = FMath::Clamp(NewPercent, 0.0f, 1.0f);
	CurrentAlpha = 0.0f;
}
