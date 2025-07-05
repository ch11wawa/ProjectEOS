// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosTitleWidget.generated.h"

class UEosTitleCharacterSelectWidget;
/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosTitleWidget : public UEosBaseWidget
{
	GENERATED_BODY()

/// ENGINE FUNCTION
private:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

/// CUSTOM FUNCTION
private:
	UFUNCTION()
	void OnClickedStart();				// Button(Start) On_Click Event

/// CUSTOM VARIABLE
private:
	// Bind Button
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Start;

	UPROPERTY(meta = (BindWidget))
	class UEditableText* EditableText_HostIP;

};
