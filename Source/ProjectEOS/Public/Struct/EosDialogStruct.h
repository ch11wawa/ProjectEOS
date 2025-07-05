// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EosDialogStruct.generated.h"

USTRUCT(BlueprintType)
struct FDialogRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NpcID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NpcName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsChoice;

	FDialogRow() : NpcID("None"), NpcName("None"), DialogText(FText::FromString("None")), NextID("None"), QuestID("None"), bIsChoice(false) {}
};
