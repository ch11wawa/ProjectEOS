// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosBaseMessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosBaseMessageWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	

/// CUSTOM FUNCTION
protected:
	UFUNCTION(BlueprintCallable)
	void SetMessage(const FText NewMessage);
	
/// CUSTOM VARIABLE
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_Message;

	
};
