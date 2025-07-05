// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TargetActorGA_GroundTrace.h"

// Ÿ���� ���� �� ȣ�� : Ability�� ��Ʈ�ѷ� ���� + ��ŸŬ(Decal) ����
void ATargetActorGA_GroundTrace::StartTargeting(UGameplayAbility* Ability)
{
    Super::StartTargeting(Ability);
    OwningAbility = Ability;
    MyReticleActor = SpawnReticleActor(GetActorLocation(), GetActorRotation());
    UE_LOG(LogTemp, Warning, TEXT("Reticle Spawn Attempt: %s"), *GetNameSafe(CustomReticleClass));
}

// �� ������ ȣ��Ǵ� ����Ʈ���̽� �Լ�
bool ATargetActorGA_GroundTrace::LineTraceFN(FHitResult& OutHit)
{
    FVector Start;
    // Character(PrimaryPC) �Ǵ� AI(MasterAIController)���� ���� ��ġ ����
    if (PrimaryPC && PrimaryPC->GetPawn())
    {
        Start = PrimaryPC->GetPawn()->GetActorLocation();
    }
    else if (MasterAIController && MasterAIController->GetPawn())
    {
        Start = MasterAIController->GetPawn()->GetActorLocation();
    }
    else return false;

    // ���� ��ġ���� �Ʒ��� MaxTargetDistance��ŭ ���
    FVector End = Start - FVector(0.f, 0.f, MaxTargetDistance);
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 2.0f);
    
    // ������ ���� ����Ʈ���̽� ����
    return GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);
}

// Ÿ���� Ȯ�� �� ȣ�� : TargetData ���� �� ��ε�ĳ��Ʈ
void ATargetActorGA_GroundTrace::ConfirmTargetingAndContinue()
{
    FHitResult Hit;
    if (LineTraceFN(Hit))
    {
        FGameplayAbilityTargetDataHandle Data;
        Data.Add(new FGameplayAbilityTargetData_SingleTargetHit(Hit));
        TargetDataReadyDelegate.Broadcast(Data);
    }
    else
    {
        TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
    }
    DestroyReticleActors();
}
