// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosTitleCharacterSelectWidget.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, const int&, CharacterClass);

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosTitleCharacterSelectWidget : public UEosBaseWidget
{
	GENERATED_BODY()

/// ENGINE FUNCTION
protected:
	virtual bool Initialize() override;

/// CUSTOM FUNCTION
private:
	UFUNCTION()
	void OnClickedCharacter();				// Button(Charcater) On_Click Event

	UFUNCTION()
	void ChangeImage(int Index, UTexture2D* NewImage);

	void CancleSelect();


/// CUSTOM VARIABLE
protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsPress;

private:
	// Bind Button
	UPROPERTY(meta=(BindWidget))
	class UButton* Button_Character;

	// Bind Image
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_CharacterImage;

	UPROPERTY(meta=(BindWidget))
	class USizeBox* SizeBox_Select;
	
	int CharacterClass;
};
