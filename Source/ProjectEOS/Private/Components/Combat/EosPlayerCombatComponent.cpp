// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EosPlayerCombatComponent.h"
#include "Items/Weapon/EosBasePlayerWeapon.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EosGameplayTags.h"
#include "Struct/EosStructTypes.h"
#include "EosFunctionLibrary.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"

AEosBasePlayerWeapon* UEosPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AEosBasePlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AEosBasePlayerWeapon* UEosPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<AEosBasePlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UEosPlayerCombatComponent::GetPlayerCurrentWeaponDamageAtLevel(float InLevel) const
{
    return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

// ��� ���� �Ǵ� �� ���� ~
float UEosPlayerCombatComponent::GetPlayerCurrentSkillDamageAtLevel(ESkillButtons InSkillButtons, float InLevel) const
{
    float OutValue = 0;
    switch (SkillButtons)
    {
    case ESkillButtons::Q:
        OutValue = GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.SkillBaseDamage.GetValueAtLevel(InLevel);
        break;

    case ESkillButtons::E:
        OutValue = GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.SkillBaseDamage.GetValueAtLevel(InLevel);
        break;

    case ESkillButtons::R:
        OutValue = GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.SkillBaseDamage.GetValueAtLevel(InLevel);
        break;

    case ESkillButtons::F:
        OutValue = GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.SkillBaseDamage.GetValueAtLevel(InLevel);
        break;
    }
    return OutValue;
}
// ~ ��� ���� �Ǵ� �� ���� 

void UEosPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    APawn* HitPawn = Cast<APawn>(HitActor);
    // Ÿ�ݵ� ���Ͱ� �迭�� ������ ����
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }
    // Ÿ�ݵ� ���͸� �迭�� ����
    OverlappedActors.AddUnique(HitActor);

    // �̺�Ʈ ������ ����
    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;
    
    // �� ���� Ȯ��
    if(UEosFunctionLibrary::CheckTargetIsEnemy(GetOwner()->GetInstigator(), HitPawn))
    {
        // ī���� ���� ���� Ȯ��
        if (UEosFunctionLibrary::NativeDoesActorHaveTag(GetOwner(), EosGameplayTags::Player_Status_Counter) && UEosFunctionLibrary::NativeDoesActorHaveTag(HitActor, EosGameplayTags::Enemy_Status_Counterable))
        {
            // ��ȿ ����(ī����) ���� Ȯ��
            if(UEosFunctionLibrary::IsValidGuard(GetOwner(), HitActor))
            {
                // ī���� ���� �߽�
                UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
                (
                    HitActor,
                    EosGameplayTags::Enemy_Event_SuccessCounter,
                    Data
                );
                UEosAbilitySystemComponent* ASC = UEosFunctionLibrary::GetNativeEosAbilitySystemComponent(GetOwner());

                // ���� �ǵ�� ȿ��(ť)
                if (ASC)
                {
                    FGameplayCueParameters Params;
                    FVector GreatSwordLocation = FVector(GetCharacterCurrentEquippedWeapon()->GetActorLocation());

                    Params.Instigator = GetOwner();
                    Params.SourceObject = GetOwner();
                    Params.Location = GreatSwordLocation;
                    Params.RawMagnitude = 0.4f;
                    
                    ASC->ExecuteGameplayCue(EosGameplayTags::GameplayCue_Feedback_HoldAnim, Params);
                }
                //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Sending Success Counter Event!!"));
                
                // ����� �߽�
                UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
                (
                    GetOwningPawn(),
                    EosGameplayTags::Common_Event_MeleeHit,
                    Data
                );
            }
        }
        else
        {
            // ����� �߽�
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
            (
                GetOwningPawn(),
                EosGameplayTags::Common_Event_MeleeHit,
                Data
            );
        }
    }
}

void UEosPlayerCombatComponent::OnEndHitFromTargetActor(AActor* HitActor)
{
}