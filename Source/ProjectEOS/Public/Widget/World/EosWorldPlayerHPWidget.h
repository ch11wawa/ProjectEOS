// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosWorldPlayerHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosWorldPlayerHPWidget : public UEosBaseWidget
{
	GENERATED_BODY()
/// ENGINE FUNCTION
protected:
	virtual void NativeConstruct() override;

/// CUSTOM FUNCTION
protected:
	UFUNCTION(BlueprintCallable)
	void UpdateHP(const float& InNewPercent);

private:
	void GetAttributeSet();

/// CUSTOM VARIABLE
private:
	UPROPERTY(meta=(BindWidget))
	class UEosWorldBaseProgressBarWidget* ProgressBar_HP;

	FTimerHandle GetAttributeSetTimer;

/// GETTER FUNCTION

/// HELPER FUNCTION



};
