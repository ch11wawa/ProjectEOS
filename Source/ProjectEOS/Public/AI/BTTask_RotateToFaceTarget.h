// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateToFaceTarget.generated.h"

// 메모리 인스턴스 구조체
struct FRotateToFaceTargetTaskMemory
{
	TWeakObjectPtr<APawn> OwningPawn;
	TWeakObjectPtr<AActor> TargetActor;

	// 유효성 검증
	bool IsValid() const
	{
		return OwningPawn.IsValid() && TargetActor.IsValid();
	}
	// 포인터 초기화
	void Reset()
	{
		OwningPawn.Reset();
		TargetActor.Reset();
	}
};

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UBTTask_RotateToFaceTarget : public UBTTaskNode
{
	GENERATED_BODY()
///ENGINE FUNCTION	
	UBTTask_RotateToFaceTarget();
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);


///CUSTOM FUCNTION
	
	bool HasReachedAnglePrecision(APawn* QueryPawn, AActor* TargetActor) const;


///CUSTOM VARIABLE
	UPROPERTY(EditAnywhere, Category = "Face Target")
	FBlackboardKeySelector InTargetToFaceKey;

	UPROPERTY(EditAnywhere, Category = "Face Target")
	float AnglePrecision;

	UPROPERTY(EditAnywhere, Category = "Face Target")
	float RotationInterpSpeed;
};
