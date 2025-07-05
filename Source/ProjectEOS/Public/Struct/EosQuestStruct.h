// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EosQuestStruct.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	None,
	Main,
	Sub,
	Daily,
	Event
};

UENUM(BlueprintType)
enum class EQuestConditionType : uint8
{
	None,
	KillMonster,
	CollectItem
};

USTRUCT(BlueprintType)
struct FQuestCondition : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestConditionType ConditionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName TargetId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RequiredAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ConditionText;

	FQuestCondition() : ConditionType(EQuestConditionType::None), TargetId("None"), RequiredAmount(0), ConditionText(FText::FromString("None")) {}
};

USTRUCT(BlueprintType)
struct FQuestRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestType QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName GiverNpcId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CompleterNpcId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestCondition> Condition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextQuestId;

	FQuestRow() : Title(FText::FromString("None")), Description(FText::FromString("None")), QuestType(EQuestType::None), GiverNpcId("None"), CompleterNpcId("None"), NextQuestId("None") {}
};
