// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/EosBaseHUD.h"
#include "Struct/EosDialogStruct.h"
#include "Enums/EosEnumTypes.h"
#include "EosVillageHUD.generated.h"

class UEosWorldPlayerHudWidget;
class UEosNPCDialogWidget;
class UEosBaseMessageWidget;
class AEosInventoryPreview;

/**
 * 
 */

UCLASS()
class PROJECTEOS_API AEosVillageHUD : public AEosBaseHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ShowMessageWidget();

	UFUNCTION(BlueprintCallable)
	void RemoveMessageWidget();

	UFUNCTION(BlueprintCallable)
	void ShowNPCDialog(const FName DialogID);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerHUD();

	UFUNCTION(BlueprintCallable)
	void SwitchingMain();

	void SwitchingInventory();
	void SwitchingSkill();
	void SwitchingMap();
	void ChangeFocus(const EEosUIModeType InUIModeType);

private:

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerHUD")
	TSubclassOf<UEosWorldPlayerHudWidget> EosWorldPlayerHudWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerHUD")
	UEosWorldPlayerHudWidget* EosWorldPlayerHudWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC")
	TSubclassOf<UEosNPCDialogWidget> EosNPCDialogWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
	UEosNPCDialogWidget* EosNPCDialogWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC")
	TSubclassOf<UEosBaseMessageWidget> EosBaseMessageWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
	UEosBaseMessageWidget* EosBaseMessageWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	EMenuStatus CurrentMenuStatus = EMenuStatus::Main;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	AEosInventoryPreview* ShowcaseStage;

private:
	APlayerController* PlayerController;
};
