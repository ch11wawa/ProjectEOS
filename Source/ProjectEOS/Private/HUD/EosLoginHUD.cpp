// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EosLoginHUD.h"
#include "Widget/Login/EosLoginWidget.h"
#include "Widget/Login/EosBaseSelectionPageWidget.h"



void AEosLoginHUD::BeginPlay()
{
	Super::BeginPlay();

	if (EosLoginWidgetClass)
	{
		EosLoginWidget = CreateWidget<UEosLoginWidget>(GetWorld(), EosLoginWidgetClass);

		if (EosLoginWidget)
		{
			EosLoginWidget->AddToViewport();
		}
	}

	SetInputMode(0);

}

void AEosLoginHUD::SwitchToMainMenu()
{
	EosLoginWidget->OnClickedBack();
}

void AEosLoginHUD::SwitchToCharacterSelection()
{
	if (EosLoginWidget && EosLoginWidget->IsInViewport())
	{
		EosLoginWidget->RemoveFromParent();
		EosLoginWidget = nullptr;
	}

	if (EosSelectionCharacterWidgetClass)
	{
		EosSelectionCharacterWidget = CreateWidget<UEosBaseSelectionPageWidget>(GetWorld(), EosSelectionCharacterWidgetClass);

		if (EosSelectionCharacterWidget)
		{
			EosSelectionCharacterWidget->AddToViewport();
		}
	}
}

void AEosLoginHUD::SwitchToCreateCharacter()
{
	if(EosSelectionCharacterWidget && EosSelectionCharacterWidget->IsInViewport())
	{
		EosSelectionCharacterWidget->RemoveFromParent();
		EosSelectionCharacterWidget = nullptr;
	}

	if (EosNewCharacterWidgetClass)
	{
		EosNewCharacterWidget = CreateWidget<UEosBaseSelectionPageWidget>(GetWorld(), EosNewCharacterWidgetClass);

		if (EosNewCharacterWidget)
		{
			EosNewCharacterWidget->AddToViewport();
		}
	}
}
