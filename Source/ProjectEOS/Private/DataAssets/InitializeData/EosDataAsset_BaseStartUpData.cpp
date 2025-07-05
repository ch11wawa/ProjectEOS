// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/InitializeData/EosDataAsset_BaseStartUpData.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/EosGameplayAbility.h"

// ���� �����Ƽ �ο� �� ����Ʈ ����
void UEosDataAsset_BaseStartUpData::GiveAbilitySystemComponent(UEosAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	check(ASC);

	// �ο� ��û
	GrantAbilities(ActivateOnGivenAbilities, ASC, ApplyLevel);
	GrantAbilities(ReactAbilities, ASC, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectsClass : StartUpGameplayEffects)
		{
			if (!EffectsClass) continue;
			
			UGameplayEffect* EffectCDO = EffectsClass->GetDefaultObject<UGameplayEffect>();
			ASC->ApplyGameplayEffectToSelf
			(
				EffectCDO,
				ApplyLevel,
				ASC->MakeEffectContext()
			);
		}
	}
}

// �����Ƽ �ο�
void UEosDataAsset_BaseStartUpData::GrantAbilities(const TArray<TSubclassOf<UEosGameplayAbility>>& InGiveAbilities, UEosAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	if (InGiveAbilities.IsEmpty()) return;

	for (const TSubclassOf<UEosGameplayAbility>Ability : InGiveAbilities)
	{
		if (!Ability) continue;
		
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = ASC->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		ASC->GiveAbility(AbilitySpec);
	}
}