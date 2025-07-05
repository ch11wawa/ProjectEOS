// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/EosAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/EosPlayerGameplayAbility.h"
#include "EosGameplayTags.h"

void UEosAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}
	// �ߵ� ���� �����Ƽ loop
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// �Էµ� Tag�� Abilities ��ġ���� ����
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		
		// ��� Ÿ������ �߰� ����
		if (InInputTag.MatchesTag(EosGameplayTags::InputTag_Toggle))
		{
			// �ߵ��Ǿ� ������ ���
			if (AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
			}
			// �ƴϸ� �ߵ� �õ�
			else 
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
		// �ߵ� �õ�
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UEosAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	// ��ȿ�� && �±� ��ġ ���� ����(����Ÿ��)
	if (InInputTag.IsValid() && InInputTag.MatchesTag(EosGameplayTags::InputTag_Guard))
	{
		// �ߵ� ���� �����Ƽ loop
		for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
		{
			// �Էµ� Tag�� Abilities ��ġ���� ���� && �ߵ� ���� ����
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
				return;
			}
		}
	}

	// ��ȿ�� && �±� ��ġ ���� ����(����Ÿ��)
	if (InInputTag.IsValid() && InInputTag.MatchesTag(EosGameplayTags::InputTag_Continue))
	{
		// �ߵ� ���� �����Ƽ loop
		for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
		{
			// �Էµ� Tag�� Abilities ��ġ���� ���� && �ߵ� ���� ����
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
				return;
			}
		}
	}
	return;
}

void UEosAbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FPlayerAbilitySet>& InWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutAbilitySpecHandles)
{
	if (InWeaponAbilities.IsEmpty()) return;
	
	// �ɷ� �迭 loop
	for (const FPlayerAbilitySet& AbilitySet : InWeaponAbilities)
	{
		// ��ȿ���� ���� GA�� �����
		if (!AbilitySet.IsValid()) continue;
		
		// ���� ����
		FGameplayAbilitySpec AbilitySpec(AbilitySet.GrantAbility);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		// ���� ���� �� �ɷ� �ο�
		OutAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UEosAbilitySystemComponent::RemoveGrantedPlayerWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	
	if (InSpecHandlesToRemove.IsEmpty()) return;

	// �ɷ� �迭 loop
	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			// �����Ƽ ����
			ClearAbility(SpecHandle);
		}
	}
	// ���� �ڵ� ����
	InSpecHandlesToRemove.Empty();
}

bool UEosAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());
	
	// �� GA ���� �迭
	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;

	// ���� �����ϰ� Tag�� ��ġ�ϴ� ��� �����Ƽ ������ �迭�� ����
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);
	
	// �ش� �迭 �������...
	if (!FoundAbilitySpecs.IsEmpty())
	{
		// �迭 ũ�� -1��ŭ(Index match) ���� �� ����
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		// �迭�� ���� �� �Է��Ͽ� �ߵ���ų �����Ƽ ����
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);

			// �̹ߵ��̸� �ߵ� �õ�
			if (!SpecToActivate->IsActive())
			{
				return TryActivateAbility(SpecToActivate->Handle);
			}
	}
	return false;
}
