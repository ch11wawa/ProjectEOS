// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "Struct/EosPlayerInfo.h"
#include "Widget/Inventory/EosInventoryMainWidget.h"
#include "EosWorldPlayerHudWidget.generated.h"

class UEosWorldAskPartyWidget;
class UWidgetSwitcher;
class UEosInventoryMainWidget;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosWorldPlayerHudWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	
/// ENGINE FUNCTION
private:
	UEosWorldPlayerHudWidget();

/// CUSTOM FUNCTION
public:
	UFUNCTION(BlueprintCallable, Category = "Boss")
	void SwitchMenu(EMenuStatus InMenuStatus);

protected:
	UFUNCTION(BlueprintCallable, Category = "Party")
	void SetPartyUI(const FPlayerInfo& PlayerInfo);

	UFUNCTION(BlueprintCallable, Category = "Party")
	void UpdatePartyUI(const FGuid TargetGuid, float HP);

	UFUNCTION(BlueprintCallable, Category = "Party")
	void PopUpAskParty(const FGuid HostGUID, const FString& HostNickName);

	UFUNCTION(BlueprintCallable, Category = "Boss")
	void ShowBossHP();

private:
	
/// CUSTOM VARIABLE
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Party")
	TArray<class UTexture2D*> FaceImageArr;

	UPROPERTY(BlueprintReadWrite, Category = "Party")
	TArray<class UEosWorldPartyWidget*> PartyArr;

	UPROPERTY(BlueprintReadWrite)
	UEosWorldAskPartyWidget* AskPartyInstance;

private:
	//스위쳐 바인딩
	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox_Manual;

	UPROPERTY(EditAnywhere, Category = "Party")
	TSubclassOf<UEosWorldAskPartyWidget> AskPartyClass;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox_AskParty;

	UPROPERTY(EditAnywhere, Category = "Boss")
	TSubclassOf<class UEosBossWidget> BossWidgetClass;

	UPROPERTY()
	class UEosBossWidget* BossWidgetInstance;

	UPROPERTY(meta=(BindWidget))
	class USizeBox* SizeBox_BossHp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_Q;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_E;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_R;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar_F;
	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UEosInventoryMainWidget* WBP_InventoryMainWidget;

/// GETTER FUNCTION
/// HELPER FUNCTION
};