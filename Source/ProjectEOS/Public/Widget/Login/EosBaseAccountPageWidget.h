// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosBaseAccountPageWidget.generated.h"

class UButton;
class UTextBlock;
class UEditableText;
class AEosLoginHUD;
class UEosGameInstance;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosBaseAccountPageWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	

/// ENGINE FUNCTION
protected:
	virtual void NativeConstruct() override;

/// CUSTOM FUNCTION
public:
	UFUNCTION()
	virtual void Init();

protected:


	UFUNCTION(BlueprintCallable)
	void SetMessage(const FText InMessage);

	UFUNCTION(BlueprintCallable)
	virtual void OnClickedLogin();

/// CUSTOM VARIABLE
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableText* EditableText_ID;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableText* EditableText_Password;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock_Message;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Button_Login;

	UPROPERTY(BlueprintReadWrite)
	FString Username;

	UPROPERTY(BlueprintReadWrite)
	FString Password;

	UPROPERTY(BlueprintReadWrite)
	FGuid GUID;
	
	UPROPERTY()
	UEosGameInstance* EosGameInstance;
};
