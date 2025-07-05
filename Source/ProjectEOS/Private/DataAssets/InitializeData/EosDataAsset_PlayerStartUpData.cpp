// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/InitializeData/EosDataAsset_PlayerStartUpData.h"
#include "Struct/EosStructTypes.h"
#include "AbilitySystem/Abilities/EosGameplayAbility.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"

// �÷��̾� ���� �����Ƽ �߰� �ο�
void UEosDataAsset_PlayerStartUpData::GiveAbilitySystemComponent(UEosAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	Super::GiveAbilitySystemComponent(ASC, ApplyLevel);

	for (const FPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.GrantAbility);
		AbilitySpec.SourceObject = ASC->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		ASC->GiveAbility(AbilitySpec);
	}
}