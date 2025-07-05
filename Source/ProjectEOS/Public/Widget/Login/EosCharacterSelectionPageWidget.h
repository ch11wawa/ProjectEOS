// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Login/EosBaseSelectionPageWidget.h"
#include "EosCharacterSelectionPageWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosCharacterSelectionPageWidget : public UEosBaseSelectionPageWidget
{
	GENERATED_BODY()

/// ENGINE FUNCTION

/// CUSTOM FUNCTION
	virtual void AddCharacterSlots();

protected:
	UFUNCTION(BlueprintPure)
	EPlayerClassType StringToECharacterClass(const FString InString);

	UFUNCTION(BlueprintCallable)
	void UpdateCharacterSlots();

	//virtual void SelectCharacter(const EPlayerClassType CharacterClass);

private:
	virtual void OnClickedSelect();

/// CUSTOM VARIABLE
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPlayerClassType> CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> NicknameArr;

	UPROPERTY(BlueprintReadWrite)
	TArray<FGuid> CidArr;

	UPROPERTY(BlueprintReadWrite)
	TArray<USizeBox*> CharacterBoxs;

private:
	//UPROPERTY(meta=(BindWidget))
	//USizeBox* SizeBox_Character1;
	//
	//UPROPERTY(meta = (BindWidget))
	//USizeBox* SizeBox_Character2;

	//UPROPERTY(meta = (BindWidget))
	//USizeBox* SizeBox_Character3;


};
