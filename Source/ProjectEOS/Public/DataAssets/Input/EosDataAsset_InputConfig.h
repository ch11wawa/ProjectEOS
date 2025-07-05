// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "EosDataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;


/**
 * 
 */
USTRUCT(BlueprintType)
struct FEosInputActionConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

/// HELPER FUNCTION
	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}

	// �⺻ ������
	FEosInputActionConfig()
		: InputTag(FGameplayTag())  // FGameplayTag�� �⺻ �����ڷ� �ʱ�ȭ
		, InputAction(nullptr)       // UInputAction*�� nullptr�� �ʱ�ȭ
	{}
};

UCLASS()
class PROJECTEOS_API UEosDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

/// ENGINE FUNCTION


/// CUSTOM FUNCTION

public:
	// �⺻ ������
	UEosDataAsset_InputConfig()
		: DefaultMappingContext(nullptr)   // UInputMappingContext*�� nullptr�� �ʱ�ȭ
		, NativeInputActions()             // TArray<FEosInputActionConfig>�� �� �迭�� �ʱ�ȭ
		, AbilityInputActions()            // TArray<FEosInputActionConfig>�� �� �迭�� �ʱ�ȭ
	{}
protected:

private:

/// CUSTOM VARIABLE

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FEosInputActionConfig> NativeInputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FEosInputActionConfig> AbilityInputActions;

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;


protected:

private:

	
};