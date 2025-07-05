// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "EosStructTypes.generated.h"

class UEosGameplayAbility;
class UInputMappingContext;
class UEosPlayerLinkedAnimLayer;
class UEosPrimaryDataAsset_ItemData;

/**
 * 
 */

//PROJECTEOS_API

USTRUCT(BlueprintType)
struct  FPlayerAbilitySet
{

	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UEosGameplayAbility> GrantAbility;

/// CUSTOM FUNCTION
	bool IsValid() const;


	// �⺻ ������
	FPlayerAbilitySet()
		: InputTag(FGameplayTag()) // FGameplayTag�� �⺻ �����ڷ� �ʱ�ȭ
		, GrantAbility(nullptr)    // TSubclassOf�� nullptr�� �ʱ�ȭ
	{}
};

USTRUCT(BlueprintType)
struct  FPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UEosPlayerLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat SkillBaseDamage;

	// �⺻ ������
	FPlayerWeaponData()
		: WeaponAnimLayerToLink(nullptr)               // TSubclassOf<UEosPlayerLinkedAnimLayer>�� nullptr�� �ʱ�ȭ
		, WeaponInputMappingContext(nullptr)           // UInputMappingContext*�� nullptr�� �ʱ�ȭ
		, DefaultWeaponAbilities()                     // TArray<FPlayerAbilitySet>�� �� �迭�� �ʱ�ȭ
		, WeaponBaseDamage(FScalableFloat(0.0f))       // FScalableFloat�� 0.0f�� �ʱ�ȭ
		, SkillBaseDamage(FScalableFloat(0.0f))        // FScalableFloat�� 0.0f�� �ʱ�ȭ
	{}
};

USTRUCT(BlueprintType)
struct  FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGuid Guid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UEosPrimaryDataAsset_ItemData> DataAssets;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 EnhancementLevel;

	// �⺻ ������
	FInventorySlot()
		: Guid(0, 0, 0, 0)
		, DataAssets(nullptr)
		, Quantity(0)
		, EnhancementLevel(0)
	{}
};