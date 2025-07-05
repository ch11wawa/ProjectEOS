// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosWorldPlayerMPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosWorldPlayerMPWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	
/// ENGINE FUNCTION

/// CUSTOM FUNCTION
protected:
	UFUNCTION(BlueprintCallable)
	void UpdateMana(const float& InNewPercent);

	UFUNCTION(BlueprintCallable)
	void UpdateStamina(const float& InNewPercent);

/// CUSTOM VARIABLE
private:
	UPROPERTY(meta = (BindWidget))
	class UEosWorldBaseProgressBarWidget* ProgressBar_MP;

/// GETTER FUNCTION

/// HELPER FUNCTION

};
