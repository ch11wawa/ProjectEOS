// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EosHUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEosHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTEOS_API IEosHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ToggleUIMode(bool EnabledMenu, UUserWidget* FocusWidget) = 0;
};
