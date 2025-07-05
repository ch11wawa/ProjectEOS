// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosWorldBaseProgressBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosWorldBaseProgressBarWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	
/// ENGINE FUNCTION
private:
	virtual void NativePreConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

/// CUSTOM FUNCTION
public:
	UFUNCTION(BlueprintCallable)
	void SetColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable)
	void UpdateBar(float NewPercent);

/// CUSTOM VARIABLE
private:
	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Fill;
	
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
