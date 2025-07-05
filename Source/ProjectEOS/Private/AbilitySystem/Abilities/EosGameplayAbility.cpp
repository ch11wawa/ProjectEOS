// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EosGameplayAbility.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"
#include "Components/Combat/EosBaseCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Skills/EosBaseProjectile.h"

void UEosGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);

    // �����Ƽ�� OnGiven�̸� ��� �ߵ�
    if (AbilityActivationPolicy == EEosAbilityActivationPolicy::OnGiven)
    {
        ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
    }
}

void UEosGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
    
    if (AbilityActivationPolicy == EEosAbilityActivationPolicy::OnGiven)
    {
        if (ActorInfo)
        {
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }
}

int32 UEosGameplayAbility::GetGameplayEffectStackCountByTag(UEosAbilitySystemComponent* ASC, TSubclassOf<UGameplayEffect> EffectClass)
{
    if(!ASC || !EffectClass) return 0;
    
    // �ߵ� ���� ��� ����Ʈ �ڵ��� ����
    FGameplayEffectQuery Query;
    const TArray<FActiveGameplayEffectHandle>& Handles = ASC->GetActiveEffects(Query);

    for (const FActiveGameplayEffectHandle& Handle : Handles)
    {
        // �ڵ� �迭�κ��� ���� �ڵ��� ����Ʈ�� �� �˻�
        const FActiveGameplayEffect* ActiveGE = ASC->GetActiveGameplayEffect(Handle);
        if (ActiveGE && ActiveGE->Spec.Def && ActiveGE->Spec.Def->GetClass() == EffectClass)
        {
            UE_LOG(LogTemp, Warning, TEXT("Matched GE: %s | StackCount: %d"), *ActiveGE->Spec.Def->GetName(), ActiveGE->Spec.GetStackCount());
            // ���ǿ� ��ġ�ϴ� ����Ʈ�� ���忡�� ���� ���� ��ȯ
            return ActiveGE->Spec.GetStackCount();
        }
    }
    // ��ġ�ϴ� �ڵ� ����
    UE_LOG(LogTemp, Warning, TEXT("GameplayEffect %s not active."), *EffectClass->GetName());
    return 0;
}

UEosBaseCombatComponent* UEosGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UEosBaseCombatComponent>();
}

UEosAbilitySystemComponent* UEosGameplayAbility::GetEosAbilitySystemComponentFromActorInfo() const
{
    return Cast<UEosAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UEosGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    // ���� ��ų ��� ������ ASC ����
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

    check(TargetASC && InSpecHandle.IsValid());

    // Ÿ�ٿ� ����Ʈ ����
    return GetEosAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget
    (
        *InSpecHandle.Data,
        TargetASC
    );
}

FActiveGameplayEffectHandle UEosGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EEosSuccessType& OutSuccessType)
{
    // ����Ʈ �ڵ� ����
    FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

    // �ڵ�� ����Ʈ ���뿩�� ���Ͽ� ������ ����
    OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EEosSuccessType::Successful : EEosSuccessType::Failed;
    
    // ����Ʈ �ڵ� ��ȯ
    return ActiveGameplayEffectHandle;
}

void UEosGameplayAbility::ApplyEffectSpecHandle(const FGameplayEffectSpecHandle& EffectSpecHandle)
{
    UE_LOG(LogTemp, Warning, TEXT("Effect applied to ability: %s"), *GetNameSafe(this));
}

AActor* UEosGameplayAbility::SpawnActorWithEffectSpec(TSubclassOf<AActor> ActorClass, FTransform SpawnTransform, const FGameplayEffectSpecHandle& EffectSpecHandle, AActor* Instigator)
{
    if (!GetWorld() || !ActorClass || !GetAvatarActorFromActorInfo()->HasAuthority())return nullptr;

    FActorSpawnParameters SpawnParms;
    SpawnParms.Owner = Instigator;
    SpawnParms.Instigator = Instigator ? Instigator->GetInstigator() : nullptr;

    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnTransform, SpawnParms);

    if (SpawnedActor)
    {
        AEosBaseProjectile* Projectile = Cast<AEosBaseProjectile>(SpawnedActor);
        if (Projectile)
        {
            Projectile->SetDamageEffectSpecHandle(EffectSpecHandle);
        }
    }
    return SpawnedActor;
}