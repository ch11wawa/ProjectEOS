// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RotateToFaceTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_RotateToFaceTarget::UBTTask_RotateToFaceTarget()
{
	// 초기화 작업
	NodeName = TEXT("Rotate to Face Target Actor");
	AnglePrecision = 10.f;
	RotationInterpSpeed = 5.f;

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	INIT_TASK_NODE_NOTIFY_FLAGS();

	// 키 매핑 & 타입제한
	InTargetToFaceKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetToFaceKey), AActor::StaticClass());
}

void UBTTask_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	// 키 초기화
	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetToFaceKey.ResolveSelectedKey(*BBAsset);
	}
}

uint16 UBTTask_RotateToFaceTarget::GetInstanceMemorySize() const
{
	// 태스크의 메모리 사이즈 리턴
	return sizeof(FRotateToFaceTargetTaskMemory);
}

FString UBTTask_RotateToFaceTarget::GetStaticDescription() const
{
	// 노드 설명 설정
	const FString KeyDescription = InTargetToFaceKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("Rotates to face %s Key until angle precisioon %s is reached"), *KeyDescription, *FString::SanitizeFloat(AnglePrecision));
}

EBTNodeResult::Type UBTTask_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 키를 통해 값 저장
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetToFaceKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	// 노드 메모리 로드
	FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
	check(Memory);
	
	// 오너,타겟 설정
	Memory->OwningPawn = OwningPawn;
	Memory->TargetActor = TargetActor;

	// 메모리 유효성 점검
	if (!Memory->IsValid())
	{
		return EBTNodeResult::Failed;
	}
	
	// 허용범위 검증
	if (HasReachedAnglePrecision(OwningPawn, TargetActor))
	{
		// 포인터 해제 및 태스크 성공
		Memory->Reset();
		return EBTNodeResult::Succeeded;
	}
	// 태스크 실패
	return EBTNodeResult::Failed;
}

void UBTTask_RotateToFaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// 노드 메모리 로드
	FRotateToFaceTargetTaskMemory* Memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);

	if (!Memory->IsValid())
	{
		// 실패
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	if (HasReachedAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
	{
		// 포인터 해제 및 태스크 성공
		Memory->Reset();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else 
	{
		// 타겟 방향 회전 보간
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Memory->OwningPawn->GetActorLocation(), Memory->TargetActor->GetActorLocation());
		const FRotator TargetRot = FMath::RInterpTo(Memory->OwningPawn->GetControlRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);
		const FRotator FlatLookAtRot = FRotator(0.f, LookAtRot.Yaw, 0.f);

		// 타겟 방향 회전 설정
		Memory->OwningPawn->SetActorRotation(FlatLookAtRot);
	}
}

bool UBTTask_RotateToFaceTarget::HasReachedAnglePrecision(APawn* QueryPawn, AActor* TargetActor) const
{
	const FVector OwnerForward = QueryPawn->GetActorForwardVector();
	const FVector OwnerToTargetNormalized = (TargetActor->GetActorLocation() - QueryPawn->GetActorLocation()).GetSafeNormal();

	// 점곱을 통해 벡터 방향차 확인
	const float DotResult = FVector::DotProduct(OwnerForward, OwnerToTargetNormalized);
	
	// 각도로 환산
	const float AngleDiff = UKismetMathLibrary::DegAcos(DotResult);

	// 허용치보다 낮거나 같으면 성공
	return AngleDiff <= AnglePrecision;
}