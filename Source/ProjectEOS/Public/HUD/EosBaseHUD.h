// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EosBaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API AEosBaseHUD : public AHUD
{
	GENERATED_BODY()

protected:

public:
	void SetInputMode(int32 mode);				// InputMode 변경 함수 (0: UI    1: Game    2: Game and UI)
};
