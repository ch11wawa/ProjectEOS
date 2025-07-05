// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/EosBaseHUD.h"
#include "EosLoginHUD.generated.h"

class UEosLoginWidget;
class UEosBaseSelectionPageWidget;

/**
 *
 */
UCLASS()
class PROJECTEOS_API AEosLoginHUD : public AEosBaseHUD
{
	GENERATED_BODY()
	/// ENGINE FUNCTION
	virtual void BeginPlay() override;

	/// CUSTOM FUNCTION
public:
	UFUNCTION(BlueprintCallable)
	void SwitchToMainMenu();

	UFUNCTION(BlueprintCallable)
	void SwitchToCharacterSelection();

	UFUNCTION(BlueprintCallable)
	void SwitchToCreateCharacter();

	/// CUSTOM VARIABLE
protected:
	UPROPERTY(EditDefaultsOnly, Category = "LoginWidget")
	TSubclassOf<UEosLoginWidget> EosLoginWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "SelectionWidget")
	TSubclassOf<UEosBaseSelectionPageWidget> EosSelectionCharacterWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "SelectionWidget")
	TSubclassOf<UEosBaseSelectionPageWidget> EosNewCharacterWidgetClass;

private:
	// ºäÆ÷Æ®¿¡ ºÙÀÏ À§Á¬
	UPROPERTY(VisibleAnywhere, Category = "LoginWidget")
	UEosLoginWidget* EosLoginWidget;

	UPROPERTY(VisibleAnywhere, Category = "SelectionWidget")
	UEosBaseSelectionPageWidget* EosSelectionCharacterWidget;

	UPROPERTY(VisibleAnywhere, Category = "SelectionWidget")
	UEosBaseSelectionPageWidget* EosNewCharacterWidget;

	/// GETTER FUNCTION

	/// HELPER FUNCTION



};
