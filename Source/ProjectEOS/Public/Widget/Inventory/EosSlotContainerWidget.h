// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosSlotContainerWidget.generated.h"

class UScrollBox;
class UUniformGridPanel;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosSlotContainerWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* GridForSlots;
};
