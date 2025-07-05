// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EosBaseWidget.generated.h"

class UEosBaseUIComponent;
class UEosPlayerUIComponent;
class UEosAttributeSet;
class AEosLoginHUD;
class AEosVillageHUD;
class AEosBasePlayerCharacter;
/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosBaseWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	UEosBaseUIComponent* BringUIComponent(AActor* Character);

	UFUNCTION(BlueprintPure)
	UEosPlayerUIComponent* BringPlayerUIComponent();

	UFUNCTION(BlueprintPure)
	UEosAttributeSet* GetEosAttributeSet();

protected:
	UFUNCTION(BlueprintPure)
	AEosLoginHUD* GetLoginHUD() const;

	UFUNCTION(BlueprintPure)
	AEosVillageHUD* GetVillageHUD() const;

	UFUNCTION(BlueprintPure)
	AEosBasePlayerCharacter* GetEosBasePlayerCharacter() const;

private:
	class UEosInventoryComponent* InventoryComponent;

	class UPanelWidget* CachedPanelWidget;
	int CachedFirstIndex;
	int CachedLastIndex;
	TSubclassOf<class UEosSlot> CachedEosSlotWidgetClass;
#pragma endregion
};
