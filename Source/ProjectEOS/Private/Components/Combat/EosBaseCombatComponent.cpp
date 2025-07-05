// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EosBaseCombatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Items/Weapon/EosBaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

void UEosBaseCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UEosBaseCombatComponent, CurrentEquippedWeaponTag);
}

void UEosBaseCombatComponent::Server_ToggleWeaponCollision_Implementation(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
    // ���� �ݸ��� ���
    ToggleWeaponCollision(bShouldEnable, ToggleDamageType);
}

void UEosBaseCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
    // ����� ����� Ÿ�� ����
    if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
    {
        // ���� ���� ����
        AEosBaseWeapon* CurrentWeapon = GetCharacterCurrentEquippedWeapon();

        check(CurrentWeapon);

        // bool ���� �����Ͽ� ON/OFF ����
        if (bShouldEnable)
        {
            CurrentWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("On QueryOnly")));
        }
        else
        {
            CurrentWeapon->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            OverlappedActors.Empty();
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("No Collision")));
        }
    }

    // �ٸ� Ÿ���� ���(�ݺ�)
    // ���� ToggleDamageType�� ���� ��ġ Ÿ���� �߰��� ��� else if�� ��ȯ �ٶ�.
    else
    {
        AEosBaseWeapon* CurrentWeapon = GetCharacterCurrentEquippedWeapon();

        check(CurrentWeapon);

        if (bShouldEnable)
        {
            CurrentWeapon->GetSubWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        }
        else
        {
            CurrentWeapon->GetSubWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            OverlappedActors.Empty();
        }
    }
}

// ���� ��� �Լ�
void UEosBaseCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTag, AEosBaseWeapon* InWeaponRegister, bool bIsRegisterAsEquippedWeapon)
{
    // �ʿ� �±� �� ���⸦ ����
    PlayerCarriedWeaponMap.Emplace(InWeaponTag, InWeaponRegister);

    // ���� ������ �ÿ� ����� ��������Ʈ�� ���ε�
    InWeaponRegister->OnWepaonHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
    InWeaponRegister->OnWeaponEndHitFromTarget.BindUObject(this, &ThisClass::OnEndHitFromTargetActor);

    // ���� ���� ���¸�...
    if (bIsRegisterAsEquippedWeapon)
    {
        // ���� ���� ���� �±� ����
        CurrentEquippedWeaponTag = InWeaponTag;
    }
}

void UEosBaseCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UEosBaseCombatComponent::OnEndHitFromTargetActor(AActor* HitActor)
{
}

AEosBaseWeapon* UEosBaseCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
    // ���� �� �����̳ʿ� �ش� �±� Ű�� �ִ� �� Ȯ��
    if (PlayerCarriedWeaponMap.Contains(InWeaponTagToGet))
    {
        // ������ ã�ƿͼ� ���⸦ ��ȯ
        if (AEosBaseWeapon* const* FoundWeapon = PlayerCarriedWeaponMap.Find(InWeaponTagToGet))
        {
            return *FoundWeapon;
        }
    }
    return nullptr;
}

AEosBaseWeapon* UEosBaseCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
    
    if(!CurrentEquippedWeaponTag.IsValid()) return nullptr;

    // ���� �������� ���� �±׸� �̿��ؼ� ���� ��ȯ
    return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}