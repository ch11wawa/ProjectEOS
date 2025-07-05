// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "Struct/EosDialogStruct.h"
#include "EosNPCDialogWidget.generated.h"



class UTextBlock;
class USizeBox;
class UButton;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosNPCDialogWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	
/// ENGINE FUNCTION
private:
	virtual void NativeConstruct() override;

/// CUSTOM FUNCTION
public:
	void SetDialogText(const FName NewDialogID);
private:
	UFUNCTION()
	void OnClickedNext();

	UFUNCTION()
	void OnClickedYes();

	UFUNCTION()
	void OnClickedNo();
	

/// CUSTOM VARIABLE
public:
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NpcID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName DialogID;

private:
	UPROPERTY()
	FDialogRow DialogRow;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Text;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox_Next;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox_Yes;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox_No;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Next;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Yes;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_No;

	UPROPERTY(meta =(BindWidget))
	UTextBlock* TextBlock_NextText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Name;

/// GETTER FUNCTION

/// HELPER FUNCTION

	
	
};
