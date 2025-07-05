// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EosTitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "Widget/Title/EosTitleWidget.h"

void AEosTitleHUD::BeginPlay()
{
	Super::BeginPlay();

	if (EosTitleWidgetClass)
	{
		EosTitleWidget = CreateWidget<UEosTitleWidget>(GetWorld(), EosTitleWidgetClass);

		if (EosTitleWidget)
		{
			EosTitleWidget->AddToViewport();
		}
	}

	SetInputMode(0);
}