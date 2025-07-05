// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EosVillageHUD.h"
#include "Blueprint/UserWidget.h"
#include "Widget/World/EosWorldPlayerHudWidget.h"
#include "GameFramework/PlayerController.h"
#include "ProjectEOS/Public/Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "Widget/NPC/EosNPCDialogWidget.h"
#include "Widget/World/EosBaseMessageWidget.h"
#include "PlayerController/EosBasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Items/Inventory/EosInventoryPreview.h"

void AEosVillageHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetOwningPlayerController();

	if (EosBaseMessageWidgetClass)
	{
		if (PlayerController)
		{
			EosBaseMessageWidget = CreateWidget<UEosBaseMessageWidget>(PlayerController, EosBaseMessageWidgetClass);
			EosBaseMessageWidget->AddToViewport();
			EosBaseMessageWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	if (EosNPCDialogWidgetClass)
	{
		if (PlayerController)
		{
			EosNPCDialogWidget = CreateWidget<UEosNPCDialogWidget>(PlayerController, EosNPCDialogWidgetClass);
			EosNPCDialogWidget->AddToViewport();
			EosNPCDialogWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	if (EosWorldPlayerHudWidgetClass)
	{
		if (PlayerController)
		{
			EosWorldPlayerHudWidget = CreateWidget<UEosWorldPlayerHudWidget>(PlayerController, EosWorldPlayerHudWidgetClass);
			EosWorldPlayerHudWidget->AddToViewport();
		}
	}

	ShowPlayerHUD();

	ShowcaseStage = Cast<AEosInventoryPreview>(UGameplayStatics::GetActorOfClass(GetWorld(), AEosInventoryPreview::StaticClass()));
}

void AEosVillageHUD::ShowMessageWidget()
{
	EosBaseMessageWidget->SetVisibility(ESlateVisibility::Visible);
}

void AEosVillageHUD::RemoveMessageWidget()
{
	EosBaseMessageWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AEosVillageHUD::ShowNPCDialog(const FName DialogID)
{
	SetInputMode(2);

	if (EosWorldPlayerHudWidget)
		EosWorldPlayerHudWidget->SetVisibility(ESlateVisibility::Collapsed);

	if(EosBaseMessageWidget)
		EosBaseMessageWidget->SetVisibility(ESlateVisibility::Collapsed);


	if (EosNPCDialogWidget)
	{
		EosNPCDialogWidget->SetDialogText(DialogID);
		EosNPCDialogWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AEosVillageHUD::ShowPlayerHUD()
{
	SetInputMode(1);

	if(GetOwningPawn())
	{
		Cast<AEosBasePlayerCharacter>(GetOwningPawn())->GetMesh()->SetVisibility(true, true);
		PlayerController->SetViewTargetWithBlend(GetOwningPawn(), 0.5f);
	}


	if (EosNPCDialogWidget)
	{
		EosNPCDialogWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (EosWorldPlayerHudWidget)
	{
		EosWorldPlayerHudWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

#pragma region SwitcingWidget
//Start SwitchingWidget~
//TODO::삼항으로 함수 개선
void AEosVillageHUD::SwitchingMain()
{
	AEosBasePlayerController* EosPlayerController = Cast<AEosBasePlayerController>(PlayerController);

	if (CurrentMenuStatus != EMenuStatus::Main)
	{
		EosWorldPlayerHudWidget->SwitchMenu(EMenuStatus::Main);
		CurrentMenuStatus = EMenuStatus::Main;
		ChangeFocus(EEosUIModeType::GameOnly);

		if (EosPlayerController)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), TEXT("RemoveMappingContext"));

			EosPlayerController->SwitchIngameMappingContext();
			//EosWorldPlayerHudWidget->WBP_InventoryMainWidget->CloseInventory();
			AEosBasePlayerCharacter* PlayerChar = Cast<AEosBasePlayerCharacter>(GetOwningPawn());
			ShowcaseStage->ExitInventoryMode(PlayerChar);
		}
	}
	return;
}

void AEosVillageHUD::SwitchingInventory()
{
	AEosBasePlayerController* EosPlayerController = Cast<AEosBasePlayerController>(PlayerController);

	if (CurrentMenuStatus != EMenuStatus::Inventory)
	{
		EosWorldPlayerHudWidget->SwitchMenu(EMenuStatus::Inventory);
		CurrentMenuStatus = EMenuStatus::Inventory;
		ChangeFocus(EEosUIModeType::GameAndUI);
		if (EosPlayerController)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), TEXT("RemoveMappingContext"));

			EosPlayerController->SwitchMenuMappingContext();
			//EosWorldPlayerHudWidget->WBP_InventoryMainWidget->OpenInventory();
			AEosBasePlayerCharacter* PlayerChar = Cast<AEosBasePlayerCharacter>(GetOwningPawn());
			ShowcaseStage->EnterInventoryMode(PlayerChar);
		}
		return;
	}
	else
	{
		EosWorldPlayerHudWidget->SwitchMenu(EMenuStatus::Main);
		CurrentMenuStatus = EMenuStatus::Main;
		ChangeFocus(EEosUIModeType::GameOnly);
		if (EosPlayerController)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), TEXT("RemoveMappingContext"));

			EosPlayerController->SwitchIngameMappingContext();
			//EosWorldPlayerHudWidget->WBP_InventoryMainWidget->CloseInventory();
			AEosBasePlayerCharacter* PlayerChar = Cast<AEosBasePlayerCharacter>(GetOwningPawn());
			ShowcaseStage->ExitInventoryMode(PlayerChar);
		}
	}
	return;
}

void AEosVillageHUD::SwitchingSkill()
{
	if (CurrentMenuStatus != EMenuStatus::Skill)
	{
		EosWorldPlayerHudWidget->SwitchMenu(EMenuStatus::Skill);
		CurrentMenuStatus = EMenuStatus::Skill;
		ChangeFocus(EEosUIModeType::GameAndUI);
		AEosBasePlayerCharacter* PlayerChar = Cast<AEosBasePlayerCharacter>(GetOwner());
		ShowcaseStage->EnterInventoryMode(PlayerChar);
	}
	else
	{
		EosWorldPlayerHudWidget->SwitchMenu(EMenuStatus::Main);
		CurrentMenuStatus = EMenuStatus::Main;
		ChangeFocus(EEosUIModeType::GameOnly);
		AEosBasePlayerCharacter* PlayerChar = Cast<AEosBasePlayerCharacter>(GetOwner());
		ShowcaseStage->ExitInventoryMode(PlayerChar);
	}
	return;
}

void AEosVillageHUD::SwitchingMap()
{
	if (CurrentMenuStatus != EMenuStatus::Map)
	{
		EosWorldPlayerHudWidget->SwitchMenu(EMenuStatus::Map);
		CurrentMenuStatus = EMenuStatus::Map;
		ChangeFocus(EEosUIModeType::GameAndUI);
		AEosBasePlayerCharacter* PlayerChar = Cast<AEosBasePlayerCharacter>(GetOwner());
		ShowcaseStage->EnterInventoryMode(PlayerChar);

	}
	else
	{
		EosWorldPlayerHudWidget->SwitchMenu(EMenuStatus::Main);
		CurrentMenuStatus = EMenuStatus::Main;
		ChangeFocus(EEosUIModeType::GameOnly);
		AEosBasePlayerCharacter* PlayerChar = Cast<AEosBasePlayerCharacter>(GetOwner());
		ShowcaseStage->ExitInventoryMode(PlayerChar);
	}
	return;
}
void AEosVillageHUD::ChangeFocus(const EEosUIModeType InUIModeType)
{
	IEosHUDInterface* Intf = Cast<IEosHUDInterface>(GetOwningPlayerController());
	if (Intf)
	{
		EEosUIModeType EosUIModeType = InUIModeType;
		UUserWidget* FocusWidget = Cast<UUserWidget>(EosWorldPlayerHudWidget);
		switch (EosUIModeType)
		{
		case EEosUIModeType::GameAndUI:
			Intf->ToggleUIMode(true, FocusWidget);
		case EEosUIModeType::UIOnly:
			Intf->ToggleUIMode(true, FocusWidget);
			break;
		case EEosUIModeType::GameOnly:
			Intf->ToggleUIMode(false, nullptr);
			break;
		default:
			break;
		}
	}
}
//~End SwitchingWidget
#pragma endregion