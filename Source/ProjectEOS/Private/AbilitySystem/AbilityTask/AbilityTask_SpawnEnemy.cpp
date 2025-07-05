// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/AbilityTask_SpawnEnemy.h"
#include "AbilitySystemComponent.h"
#include "Engine/AssetManager.h"
#include "NavigationSystem.h"
#include "Character/EnemyCharacter/EosBaseEnemyCharacter.h"

UAbilityTask_SpawnEnemy* UAbilityTask_SpawnEnemy::WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<AEosBaseEnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius)
{
	// ���ȭ
	UAbilityTask_SpawnEnemy* Node = NewAbilityTask<UAbilityTask_SpawnEnemy>(OwningAbility);
	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnOrigin = SpawnOrigin;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;

	return Node;
}

void UAbilityTask_SpawnEnemy::Activate()
{
	// �±׷� �ݹ� ���ε�
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	// ��ȯ ���ε�
	DelegateHandle = Delegate.AddUObject(this, &ThisClass::OnGameplayEventReceived);
}

void UAbilityTask_SpawnEnemy::OnDestroy(bool bInOwnerFinished)
{
	// �±׷� ���ε� ����
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

	Delegate.Remove(DelegateHandle);
	
	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_SpawnEnemy::OnGameplayEventReceived(const FGameplayEventData* InPlayload)
{
	if (ensure(!CachedSoftEnemyClassToSpawn.IsNull()))
	{
		// ����Ʈ ������Ʈ �񵿱� �ε�
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad
		(
			CachedSoftEnemyClassToSpawn.ToSoftObjectPath(),
			// �ε� �Ϸ� ��������Ʈ ���ε�
			FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded)
		);
	}
	else
	{
		// Ŭ���� ��������� ��ȯ ���� ���
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AEosBaseEnemyCharacter*>());
		}
		// �½�ũ ����
		EndTask();
		return;
	}
}

void UAbilityTask_SpawnEnemy::OnEnemyClassLoaded()
{
	UClass* LoadedClass = CachedSoftEnemyClassToSpawn.Get();
	UWorld* World = GetWorld();

	// �ε� ���� Ȥ�� ���� ���ؽ�Ʈ ���� �� ���� ��������Ʈ ���
	if (!LoadedClass || !World)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AEosBaseEnemyCharacter*>());
		}
		// �½�ũ ����
		EndTask();
		return;
	}

	TArray<AEosBaseEnemyCharacter*> SpawnedEnemies;

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < CachedNumToSpawn; i++)
	{
		FVector RandomLocation;
		// ���� ����Ʈ ����
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(World, CachedSpawnOrigin, RandomLocation, CachedRandomSpawnRadius);
		
		// �ణ�� ���߿��� ��ȯ
		RandomLocation += FVector(0.f, 0.f, 150.f);
		// �������� ���� ��
		const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

		AEosBaseEnemyCharacter* SpawnedEnemy = World->SpawnActor<AEosBaseEnemyCharacter>(LoadedClass, RandomLocation, SpawnFacingRotation);
		if (SpawnedEnemy)
		{
			SpawnedEnemies.Add(SpawnedEnemy);
		}
		// �½�ũ ��ȿ�� �˻�
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			// ��ü ���� �Ǿ�����
			if (!SpawnedEnemies.IsEmpty())
			{
				// �Ϸ� ���
				OnSpawnFinished.Broadcast(SpawnedEnemies);
			}
			else
			{
				DidNotSpawn.Broadcast(TArray<AEosBaseEnemyCharacter*>());
			}

			EndTask();
		}
	}
}
