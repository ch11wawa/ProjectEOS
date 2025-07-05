// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Login/EosBaseAccountPageWidget.h"
#include "EosLoginPageWidget.generated.h"

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
class PROJECTEOS_API UEosLoginPageWidget : public UEosBaseAccountPageWidget
{
	GENERATED_BODY()

/// ENGINE FUNCTION
private:
	virtual void NativeConstruct() override;

/// CUSTOM FUNCTION
public:
	//UFUNCTION()
	//void Init();

protected:
	virtual void OnClickedLogin();

private:

	//UFUNCTION()
	//void OnClickedLogin();

	//UFUNCTION()
	//void OnClickedSelect();

	//// 동적으로 위젯 추가
	//UFUNCTION(BlueprintCallable)
	//void AddCharacterBtn();

	//// 동적으로 추가된 위젯 제어
	//UFUNCTION(BlueprintCallable)
	//void SelectCharacter(const int& CharacterClass);
	
/// CUSTOM VARIABLE
protected:
	//// 캐릭터 이미지 담은 배열
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SelectCharacter")
	//TArray<UTexture2D*> CharacterImages;

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//UWidgetSwitcher* WidgetSwitcher_LoginPage;

private:
	//UPROPERTY(meta = (BindWidget))
	//UButton* Button_Login;

	//UPROPERTY(meta = (BindWidget))
	//UEditableText* EditableText_NickName;

	//UPROPERTY(meta = (BindWidget))
	//class UHorizontalBox* HorizontalBox_CharacterBox;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* Button_Select;

	//UPROPERTY(EditAnywhere, Category = "SelectCharacter")
	//TSubclassOf<UEosTitleCharacterSelectWidget> TCSWClass;

	//UPROPERTY()
	//UEosTitleCharacterSelectWidget* TCSWInstance;

	//TArray<UEosTitleCharacterSelectWidget*> CharacterButtons;

	//int SelectCharacterClass = -1;

};
