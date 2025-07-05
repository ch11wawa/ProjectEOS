// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/EosDataAsset_InputConfig.h"
#include "EosEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

/// TEMPLATE FUNCTION DECLARE
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UEosDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UEosDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);

/// CUSTOM FUNCTION



/// CUSTOM VARIABLE



};

/// TEMPLATE FUNCTION DEFINE
template<class UserObject, typename CallbackFunc>
inline void UEosEnhancedInputComponent::BindNativeInputAction(const UEosDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	check(InInputConfig);
	checkf(InInputConfig, TEXT("Input Config data assets is null"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		// Ʈ���� Ÿ������ ���ε�
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UEosEnhancedInputComponent::BindAbilityInputAction(const UEosDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input Config data assets is null"));

	// Config���� ����ü ����
	for (FEosInputActionConfig EosInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!EosInputActionConfig.IsValid()) continue;
		// ������, ������ ���·� ���ε�
		BindAction(EosInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, EosInputActionConfig.InputTag);
		BindAction(EosInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, EosInputActionConfig.InputTag);
	}
}