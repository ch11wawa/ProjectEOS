// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/AbilityTask_AbilityTick.h"

UAbilityTask_AbilityTick::UAbilityTask_AbilityTick()
{
	// ƽ ���� ����
	bTickingTask = true;
}

UAbilityTask_AbilityTick* UAbilityTask_AbilityTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	// �½�ũ �ν��Ͻ� ����
	UAbilityTask_AbilityTick* Node = NewAbilityTask<UAbilityTask_AbilityTick>(OwningAbility);

	return Node;
}

void UAbilityTask_AbilityTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	// �����Ƽ & �½�ũ ��ȿ�� ����
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		// ��ȿ�ϸ� ��������Ʈ�� ���� ��ŸŸ�� ����
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}