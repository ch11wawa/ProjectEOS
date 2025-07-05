// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosWorldPlayerChatWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECTEOS_API UEosWorldPlayerChatWidget : public UEosBaseWidget
{
	GENERATED_BODY()

///ENGINE FUNCTION
public:
	virtual void NativeConstruct() override;

///CUSTOM FUNCTION 
protected:
	UFUNCTION(BlueprintCallable)
	void UpdateMessages(const FText& InMessage);

	UFUNCTION(BlueprintCallable)
	void UpdateSystemMessages(const FText& InMessage);

	UFUNCTION()
	void FocusEditableTextBox();

private:
	void Init();

	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

///CUSTOM VARIABLE
private:
	// Bind ScrollBox
	UPROPERTY(meta = (BindWiget))
	class UScrollBox* ScrollBox_ChatBox;

	UPROPERTY(meta=(BindWidget))
	class UEditableTextBox* EditableTextBox_Chat;

	FTimerHandle GetUIComponentTimer;
};
