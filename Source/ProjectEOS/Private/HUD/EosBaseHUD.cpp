// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/EosBaseHUD.h"

// InputMode 변경 함수 (0: UI    1: Game    2: Game and UI)
void AEosBaseHUD::SetInputMode(int32 mode)
{
	if (!IsValid(GetOwningPlayerController()))
	{
		return;
	}

	FInputModeUIOnly UIOnly;
	FInputModeGameOnly GameOnly;
	FInputModeGameAndUI GameAndUI;

	switch (mode)
	{
	case 0:
		GetOwningPlayerController()->SetInputMode(UIOnly);
		GetOwningPlayerController()->SetShowMouseCursor(true);
		break;

	case 1:
		GetOwningPlayerController()->SetInputMode(GameOnly);
		GetOwningPlayerController()->SetShowMouseCursor(false);
		break;

	case 2:
		GetOwningPlayerController()->SetInputMode(GameAndUI);
		GetOwningPlayerController()->SetShowMouseCursor(true);
		break;
	};
}