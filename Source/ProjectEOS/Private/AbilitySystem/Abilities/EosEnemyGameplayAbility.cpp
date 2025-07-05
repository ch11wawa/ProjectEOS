// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EosEnemyGameplayAbility.h"
#include "AbilitySystem/Abilities/EosGameplayAbility.h"
#include "Character/EnemyCharacter/EosBaseEnemyCharacter.h"
#include "Components/Combat/EosEnemyCombatComponent.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"
#include "EosGameplayTags.h"

AEosBaseEnemyCharacter* UEosEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedBaseEnemyCharacter.IsValid())
	{
		CachedBaseEnemyCharacter = Cast<AEosBaseEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedBaseEnemyCharacter.IsValid() ? CachedBaseEnemyCharacter.Get() : nullptr;
}

UEosEnemyCombatComponent* UEosEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UEosEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);
	// ���ؽ�Ʈ �ڵ� ����
	FGameplayEffectContextHandle ContextHandle = GetEosAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	// ���� �ڵ� ����
	FGameplayEffectSpecHandle EffectSpecHandle = GetEosAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec
	(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	// �Ű������� ���� ������� SetByCaller�� ����
	EffectSpecHandle.Data->SetSetByCallerMagnitude
	(
		EosGameplayTags::Common_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);
	return EffectSpecHandle;
}

FGameplayEffectSpecHandle UEosEnemyGameplayAbility::MakeEnemyUnderAttackEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, AActor* InInstigator, float InLevel)
{
	check(EffectClass);
	// ���ؽ�Ʈ �ڵ� ����
	FGameplayEffectContextHandle ContextHandle = GetEosAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(InInstigator, InInstigator);

	// ���� �ڵ� ����
	FGameplayEffectSpecHandle EffectSpecHandle = GetEosAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec
	(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	return EffectSpecHandle;
}