// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RotateToFaceTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RotateToFaceTarget::UBTTask_RotateToFaceTarget()
{
	// �ʱ�ȭ �۾�
	NodeName = TEXT("Rotate to Face Target Actor");
	AnglePrecision = 10.f;
	RotationInterpSpeed = 5.f;

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	INIT_TASK_NODE_NOTIFY_FLAGS();

	// Ű ���� & Ÿ������
	InTargetToFaceKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetToFaceKey), AActor::StaticClass());
}

void UBTTask_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	// Ű �ʱ�ȭ
	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetToFaceKey.ResolveSelectedKey(*BBAsset);
	}
}

uint16 UBTTask_RotateToFaceTarget::GetInstanceMemorySize() const
{
	// �½�ũ�� �޸� ������ ����
	return sizeof(FRotateToFaceTargetTaskMemory);
}

FString UBTTask_RotateToFaceTarget::GetStaticDescription() const
{
	// ��� ���� ����
	const FString KeyDescription = InTargetToFaceKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("Rotates to face %s Key until angle precisioon %s is reached"), *KeyDescription, *FString::SanitizeFloat(AnglePrecision));
}

EBTNodeResult::Type UBTTask_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Ű�� ���� �� ����
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetToFaceKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	// ��� �޸� �ε�
	FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
	check(Memory);
	
	// ����,Ÿ�� ����
	Memory->OwningPawn = OwningPawn;
	Memory->TargetActor = TargetActor;

	// �޸� ��ȿ�� ����
	if (!Memory->IsValid())
	{
		return EBTNodeResult::Failed;
	}
	
	// ������ ����
	if (HasReachedAnglePrecision(OwningPawn, TargetActor))
	{
		// ������ ���� �� �½�ũ ����
		Memory->Reset();
		return EBTNodeResult::Succeeded;
	}
	// �½�ũ ����
	return EBTNodeResult::Failed;
}

void UBTTask_RotateToFaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// ��� �޸� �ε�
	FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);

	if (!Memory->IsValid())
	{
		// ����
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	if (HasReachedAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
	{
		// ������ ���� �� �½�ũ ����
		Memory->Reset();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else 
	{
		// Ÿ�� ���� ȸ�� ����
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Memory->OwningPawn->GetActorLocation(), Memory->TargetActor->GetActorLocation());
		const FRotator TargetRot = FMath::RInterpTo(Memory->OwningPawn->GetControlRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);
		const FRotator FlatLookAtRot = FRotator(0.f, LookAtRot.Yaw, 0.f);

		// Ÿ�� ���� ȸ�� ����
		Memory->OwningPawn->SetActorRotation(FlatLookAtRot);
	}
}

bool UBTTask_RotateToFaceTarget::HasReachedAnglePrecision(APawn* QueryPawn, AActor* TargetActor) const
{
	const FVector OwnerForward = QueryPawn->GetActorForwardVector();
	const FVector OwnerToTargetNormalized = (TargetActor->GetActorLocation() - QueryPawn->GetActorLocation()).GetSafeNormal();

	// ������ ���� ���� ������ Ȯ��
	const float DotResult = FVector::DotProduct(OwnerForward, OwnerToTargetNormalized);
	
	// ������ ȯ��
	const float AngleDiff = UKismetMathLibrary::DegAcos(DotResult);

	// ���ġ���� ���ų� ������ ����
	return AngleDiff <= AnglePrecision;
}