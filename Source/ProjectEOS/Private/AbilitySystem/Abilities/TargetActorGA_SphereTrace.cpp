// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TargetActorGA_SphereTrace.h"

// Ÿ���� ���� �� ȣ�� : Ability�� ��Ʈ�ѷ� ���� + ��ŸŬ(Decal) ����
void ATargetActorGA_SphereTrace::StartTargeting(UGameplayAbility* Ability)
{
    Super::StartTargeting(Ability);
    OwningAbility = Ability;
    MyReticleActor = SpawnReticleActor(GetActorLocation(), GetActorRotation());
    UE_LOG(LogTemp, Warning, TEXT("Reticle Spawn Attempt: %s"), *GetNameSafe(CustomReticleClass));
}

// ī�޶� ���� �������� ���� -> ������ Ž���ϴ� ����Ʈ���̽�
bool ATargetActorGA_SphereTrace::LineTraceFN(FHitResult& OutHit)
{
    FVector ViewPoint;
    FRotator ViewRot;
    // Character(PrimaryPC) �Ǵ� AI(MasterAIController)�κ��� ���� ���
    if (PrimaryPC) PrimaryPC->GetPlayerViewPoint(ViewPoint, ViewRot);
    else if (MasterAIController)
    {
        APawn* Pawn = MasterAIController->GetPawn();
        if (!Pawn) return false;
        ViewPoint = Pawn->GetActorLocation();
        ViewRot = Pawn->GetActorRotation();
    }
    else return false;

    //ī�޶� ���� �������� ����Ʈ���̽��ؼ� ���� ����� ���� ��´�
    FVector TraceStart = ViewPoint;
    FVector TraceEnd = TraceStart + ViewRot.Vector() * MaxTargetDistance;;

    FHitResult LineHit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(SphereTraceForward), false);
    // ���� ĳ���ʹ� Ʈ���̽� ����
    if (APawn* IgnoredPawn = PrimaryPC ? PrimaryPC->GetPawn() : (MasterAIController ? MasterAIController->GetPawn() : nullptr))
    {
        Params.AddIgnoredActor(IgnoredPawn);
    }

    // ���� �������� 1�� ����Ʈ���̽�
    if (GetWorld()->LineTraceSingleByChannel(LineHit, TraceStart, TraceEnd, ECC_Visibility, Params))
    {
        //ù ��° �浹 ���� ���� 300, �Ʒ��� 1000���� 2�� ���� Ʈ���̽�
        FVector GroundStart = LineHit.ImpactPoint + FVector(0, 0, 300.f);
        FVector GroundEnd = LineHit.ImpactPoint - FVector(0, 0, 1000.f);

        FHitResult GroundHit;
        if (GetWorld()->LineTraceSingleByChannel(GroundHit, GroundStart, GroundEnd, ECC_Visibility, Params))
        {
            //���� ��Ʈ ���� ����
            OutHit = GroundHit;

            DrawDebugSphere(GetWorld(), OutHit.ImpactPoint, 30.f, 12, FColor::Green, false, 2.0f);
            return true;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("SPHERE TRACE RUNNING"))
    return false;
}

// Ÿ���� Ȯ�� �� ȣ�� : Ʈ���̽� ���� ���ο� ���� TargetData ���� �� ��ε�ĳ��Ʈ
void ATargetActorGA_SphereTrace::ConfirmTargetingAndContinue()
{
    FHitResult Hit;
    if (LineTraceFN(Hit))
    {
        FGameplayAbilityTargetDataHandle Data;
        // Hit ������ ����
        Data.Add(new FGameplayAbilityTargetData_SingleTargetHit(Hit));
        // Hit ������ ����
        TargetDataReadyDelegate.Broadcast(Data);
    }
    else
    {
        TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
    }
    DestroyReticleActors();
}
