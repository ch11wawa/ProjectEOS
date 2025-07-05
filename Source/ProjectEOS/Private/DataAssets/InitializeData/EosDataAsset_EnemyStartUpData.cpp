// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/InitializeData/EosDataAsset_EnemyStartUpData.h"
#include "AbilitySystem/Abilities/EosEnemyGameplayAbility.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"

// ���ʹ� ���� �����Ƽ �߰� �ο�
void UEosDataAsset_EnemyStartUpData::GiveAbilitySystemComponent(UEosAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	Super::GiveAbilitySystemComponent(ASC, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UEosEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = ASC->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			ASC->GiveAbility(AbilitySpec);
		}
	}
}