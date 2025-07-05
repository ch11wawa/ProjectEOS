// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Login/EosBaseSelectionPageWidget.h"
#include "EosCreateCharacterPageWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosCreateCharacterPageWidget : public UEosBaseSelectionPageWidget
{
	GENERATED_BODY()

/// ENGINE FUNCTION
protected:
	virtual void NativeConstruct() override;

/// CUSTOM VARIABLE
protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsClicked;
	
};
