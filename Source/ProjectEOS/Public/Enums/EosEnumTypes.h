// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM()
enum class EEosConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EEosValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EEosSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EEosUIModeType : uint8
{
	UIOnly,
	GameAndUI,
	GameOnly
};

UENUM(BlueprintType)
enum class EMenuStatus : uint8
{
	Main,
	Menu,
	Inventory,
	Skill,
	Map
};
