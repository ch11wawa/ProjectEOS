// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TargetActorGA_SingleLineTrace.h"

// Ÿ���� ���� �� ȣ�� : Ability�� ��Ʈ�ѷ� ���� + ��ŸŬ(Decal) ����
void ATargetActorGA_SingleLineTrace::StartTargeting(UGameplayAbility* Ability)
{
    //�θ𿡼� Character(PrimaryPC) �Ǵ� AI(MasterAIController) ����
    Super::StartTargeting(Ability);
    OwningAbility = Ability;
    MyReticleActor = SpawnReticleActor(GetActorLocation(), GetActorRotation());
    UE_LOG(LogTemp, Warning, TEXT("Reticle Spawn Attempt: %s"), *GetNameSafe(CustomReticleClass));
}

//ī�޶�(�Ǵ� AI) ���� ���� �������� ����Ʈ���̽�
bool ATargetActorGA_SingleLineTrace::LineTraceFN(FHitResult& OutHit)
{
    FVector ViewPoint;
    FRotator ViewRot;

    // �÷��̾� ��Ʈ�ѷ����� �þ� ��������
    if (PrimaryPC) PrimaryPC->GetPlayerViewPoint(ViewPoint, ViewRot);
    else if (MasterAIController)
    {
        APawn* Pawn = MasterAIController->GetPawn();
        if (!Pawn) return false;
        ViewPoint = Pawn->GetActorLocation();
        ViewRot = Pawn->GetActorRotation();
    }
    else return false;

    // Ʈ���̽� ����, �� ���
    FVector Start = ViewPoint;
    FVector End = Start + ViewRot.Vector() * MaxTargetDistance;
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 2.0f);

    // ����Ʈ���̽� ����
    return GetWorld()->LineTraceSingleByChannel(OutHit, ViewPoint, ViewPoint + ViewRot.Vector() * MaxTargetDistance, ECC_Visibility);
}

// Ÿ�� Ȯ�� �� TargetData ���� �� ����
void ATargetActorGA_SingleLineTrace::ConfirmTargetingAndContinue()
{
    FHitResult Hit;
    FGameplayTag GameTag;
    if (LineTraceFN(Hit))
    {
        HandleEffectProjectile(Hit, GameTag);
        FGameplayAbilityTargetDataHandle TargetData;
        FGameplayAbilityTargetData_SingleTargetHit* HitData = new FGameplayAbilityTargetData_SingleTargetHit(Hit);
        TargetDataReadyDelegate.Broadcast(TargetData);
    }
    else
    {
        TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
    }
    DestroyReticleActors();
}
