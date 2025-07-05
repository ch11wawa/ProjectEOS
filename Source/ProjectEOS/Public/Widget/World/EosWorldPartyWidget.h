// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosWorldPartyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosWorldPartyWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	
/// ENGINE FUNCTION

/// CUSTOM FUNCTION
public:
	UFUNCTION()
	void UpdatePartyHP(float NewHP);

	UFUNCTION()
	void SetPartyUI(const FText& NewNickName, UTexture2D* NewImage);

/// CUSTOM VARIABLE
protected:
	UPROPERTY(BlueprintReadOnly)
	float SoulAlpha = 1;

private:
	// Bind Image
	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Face;

	UPROPERTY(meta=(BindWidget))
	class UImage* Image_Soul;

	// Bind TextBlock
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_NickName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_HPPercent;

	UPROPERTY()
	FGuid PlayerGuid;

/// GETTER FUNCTION
public:
	UFUNCTION()
	FGuid GetPartyGuid() const;

	UFUNCTION()
	void SetPartyGuid(const FGuid TargetGuid);

/// HELPER FUNCTION
};
