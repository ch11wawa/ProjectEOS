// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/EosBaseHUD.h"
#include "EosTitleHUD.generated.h"

class UEosTitleWidget;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API AEosTitleHUD : public AEosBaseHUD
{
	GENERATED_BODY()

/// ENGINE FUNCTION
protected:
	virtual void BeginPlay() override;

/// CUSTOM FUNCTION

/// CUSTOM VARIABLE
public:
	// À§Á¬ Å¬·¡½º
	UPROPERTY(EditDefaultsOnly, Category = "TitleWidget")
	TSubclassOf<UEosTitleWidget> EosTitleWidgetClass;

	// ºäÆ÷Æ®¿¡ ºÙÀÏ À§Á¬
	UPROPERTY(VisibleAnywhere, Category = "TitleWidget")
	UEosTitleWidget* EosTitleWidget;

/// GETTER FUNCTION
/// HELPER FUNCTION	
};
