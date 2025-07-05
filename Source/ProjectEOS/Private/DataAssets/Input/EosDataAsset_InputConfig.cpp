// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/EosDataAsset_InputConfig.h"
// ���� ��û�� �±װ� �迭�� �ִ� �� Ȯ��
UInputAction* UEosDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FEosInputActionConfig& InputActionConfig : NativeInputActions)
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			// ������ IA ��ȯ
			return InputActionConfig.InputAction;
		}
	return nullptr;
}
