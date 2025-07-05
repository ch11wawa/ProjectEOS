// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosBossWidget.generated.h"

class UEosBaseUIComponent;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosBossWidget : public UEosBaseWidget
{
	GENERATED_BODY()
/// ENGINE FUNCTION
private:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

/// CUSTOM FUNCTION
protected:
	UFUNCTION(BlueprintCallable)
	void UpdateHP(float CurrentHealth, float MaxHealth);
private:
	void SetBackgroundColor(FLinearColor NewColor);

/// CUSTOM VARIABLE
private:
	UPROPERTY(meta=(BindWiget))
	class UImage* ProgressBar_Background;

	UPROPERTY(meta=(BindWidget))
	class UImage* ProgressBar_Boss;

	UPROPERTY(EditAnywhere, Category = "HP")
	float TotalLines = 10.0f;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextBlock_BossName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_BossNameEn;

	UEosBaseUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere)
	FLinearColor Color;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* ProgressBarMaterial;

	UPROPERTY(VisibleAnywhere)
	class UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY()
	float Percent;

	UPROPERTY(EditAnywhere)
	float ResponseTime;

	float PreviousPercent;

	float CurrentAlpha;
	
/// GETTER FUNCTION
/// HELPER FUNCTION
};
