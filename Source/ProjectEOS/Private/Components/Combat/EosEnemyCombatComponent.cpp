// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EosEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EosGameplayTags.h"
#include "EosFunctionLibrary.h"

void UEosEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    APawn* HitPawn = Cast<APawn>(HitActor);
    APawn* OwnerPawn = Cast<APawn>(GetOwner()->GetInstigator());
    // �ǰ��ڰ� �̹� �迭�� �ִٸ� �ߴ�
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }
    
    // �迭�� ���ٸ� �߰�
    OverlappedActors.AddUnique(HitActor);

    // �̺�Ʈ ������ ����
    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    // ���� & ö�� �� �÷��̾� ���� ���� Ȯ��
	bool bIsValidGuard = false;
    bool bIsvalidRevenge = false;
	const bool bIsPlayerGuard = UEosFunctionLibrary::NativeDoesActorHaveTag(HitActor, EosGameplayTags::Player_Status_Guarding);
    const bool bIsPlayerIronwall = UEosFunctionLibrary::NativeDoesActorHaveTag(HitActor, EosGameplayTags::Player_Status_GreatSword_Ironwall);

    // ���� ���̸� ���� ���� �̺�Ʈ �߼�
	if (bIsPlayerGuard)
	{
		bIsValidGuard = UEosFunctionLibrary::IsValidGuard(GetOwner(), HitActor);
        if (bIsValidGuard)
        {
            UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
            (
                HitActor,
                EosGameplayTags::Player_Event_GuardSuccess,
                Data
            );
            return;
        }
	}

    // ö�� ���̸� ö�� ���� �̺�Ʈ �߼�
    if (bIsPlayerIronwall)
    {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
        (
            HitActor,
            EosGameplayTags::Player_Event_GreatSword_SuccessIronwall,
            Data
        );
    }
    
    // ���尡 �ƴ� ��� ���� ����� ó��
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
    (
        GetOwningPawn(),
        EosGameplayTags::Common_Event_MeleeHit,
        Data
    );

}

void UEosEnemyCombatComponent::OnEndHitFromTargetActor(AActor* HitActor)
{
}