// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosLoginWidget.generated.h"

class UButton;
class USizeBox;
class UTextBlock;
class UEditableText;
class UWidgetSwitcher;
class UEosTitleCharacterSelectWidget;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosLoginWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	
	
/// ENGINE FUNCTION
private:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

/// CUSTOM FUNCTION
public:
	UFUNCTION()
	void OnClickedBack();

private:
	UFUNCTION()
	virtual void Init();

	UFUNCTION()
	void OnClickedLoginPage();

	UFUNCTION()
	void OnClickedSignupPage();



/// CUSTOM VARIABLE

private:
	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher_Account;

	UPROPERTY(meta=(BindWiget))
	class UEosSignupPageWidget* SignupPageWidget;

	UPROPERTY(meta=(BindWidget))
	class UEosLoginPageWidget* LoginPageWidget;

	UPROPERTY(meta=(BindWidget))
	UButton* Button_LoginPage;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_SignupPage;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Back;

	/// GETTER FUNCTION
	/// HELPER FUNCTION
	
};
