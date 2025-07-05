// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Login/EosBaseAccountPageWidget.h"
#include "EosSignupPageWidget.generated.h"

class UButton;
class USizeBox;
class UTextBlock;
class UEditableText;
class AEosLoginHUD;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosSignupPageWidget : public UEosBaseAccountPageWidget
{
	GENERATED_BODY()
	
/// ENGINE FUNCTION
private:
	virtual void NativeConstruct() override;

/// CUSTOM FUNCTION
public:
	virtual void Init() override;

protected:
	virtual void OnClickedLogin();

	UFUNCTION(BlueprintCallable)
	void UsernameDuplicateCheck();

	UFUNCTION(BlueprintPure)
	bool IsAlphaOrNumber(const FString& InString);

	UFUNCTION(BlueprintPure)
	bool IsVaildPassword(const FString& InString);

/// CUSTOM VARIABLE
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableText* EditableText_ConfirmPassword;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* SizeBox_IDCheck;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USizeBox* SizeBox_Singup;

	UPROPERTY(BlueprintReadWrite, Category = "Signup")
	TArray<FString> ExistedUsername;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Username")
	int32 UsernameMinLength = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Username")
	int32 UsernameMaxLength = INT_MAX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Password")
	int32 PasswordMinLength = 7;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Password")
	int32 PasswordMaxLength = 16;

	UPROPERTY(BlueprintReadWrite)
	bool bPassID;

	UPROPERTY(BlueprintReadWrite)
	bool bPassPassword;

private:
	FString CheckedUsername;
};
