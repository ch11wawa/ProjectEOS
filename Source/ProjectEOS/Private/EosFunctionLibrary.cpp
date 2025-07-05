// Fill out your copyright notice in the Description page of Project Settings.


#include "EosFunctionLibrary.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/Combat/EosBaseCombatComponent.h"
#include "Interfaces/EosCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "EosGameplayTags.h"
#include "GenericTeamAgentInterface.h"
#include "Engine/Engine.h"

UEosAbilitySystemComponent* UEosFunctionLibrary::GetNativeEosAbilitySystemComponent(AActor* InActor)
{
	if (!ensureMsgf(InActor, TEXT("InActor is not valid from GetNativeEosAbilitySystemComponent()"))) return nullptr;

	return Cast<UEosAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UEosFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UEosAbilitySystemComponent* ASC = GetNativeEosAbilitySystemComponent(InActor);

	if (!ensureMsgf(ASC, TEXT("InActor is not valid from GetNativeEosAbilitySystemComponent()"))) return;
	// �±� ����
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

void UEosFunctionLibrary::RemoveReplicatedGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UEosAbilitySystemComponent* ASC = GetNativeEosAbilitySystemComponent(InActor);

	if (!ensureMsgf(ASC, TEXT("InActor is not valid from GetNativeEosAbilitySystemComponent()"))) return;
	// �±� ����
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveReplicatedLooseGameplayTag(TagToRemove);
	}
}

void UEosFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UEosAbilitySystemComponent* ASC = GetNativeEosAbilitySystemComponent(InActor);
	
	if (!ensureMsgf(ASC, TEXT("InActor is not valid from GetNativeEosAbilitySystemComponent()"))) return;
	// �±� �߰�
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UEosFunctionLibrary::AddReplicatedGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UEosAbilitySystemComponent* ASC = GetNativeEosAbilitySystemComponent(InActor);

	if (!ensureMsgf(ASC, TEXT("InActor is not valid from GetNativeEosAbilitySystemComponent()"))) return;
	// �±� �߰�
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddReplicatedLooseGameplayTag(TagToAdd);
	}
}

bool UEosFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UEosAbilitySystemComponent* ASC = GetNativeEosAbilitySystemComponent(InActor);
	// �±� ���� ����
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UEosFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EEosConfirmType& OutConfirmType)
{
	// �±� ���� ���� ��û �� ��ȿ ���� ��ȯ
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EEosConfirmType::Yes : EEosConfirmType::No;
}

UEosBaseCombatComponent* UEosFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	//check(InActor);

	if(IEosCombatInterface* BaseCombatInterface = Cast<IEosCombatInterface>(InActor))
	{
		// ���� ������Ʈ ��ȯ
		return BaseCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UEosBaseCombatComponent* UEosFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EEosValidType& OutValidType)
{
	// ���� ������Ʈ ��ȯ ��û
	UEosBaseCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	// ��ȿ ���� ��ȯ
	OutValidType = CombatComponent ? EEosValidType::Valid : EEosValidType::Invalid;
	
	return CombatComponent;
}

float UEosFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFlaot, float InLevel)
{
	// ������ ���� ScalableFloat ��ȯ
	return InScalableFlaot.GetValueAtLevel(InLevel);
}

bool UEosFunctionLibrary::IsListenServer(UObject* WorldContextObject)
{
	// ���� ���� ���� ��ȯ
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		return World->GetNetMode() == NM_ListenServer;
	}
	return false;
}

bool UEosFunctionLibrary::IsValidGuard(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	// �����ڿ� ������� ���溤�͸� ����
	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());
	
	// �����
	const FString GuardValid = FString::Printf(TEXT("Dot Result: %f, %s"), DotResult, DotResult < 0.f ? TEXT("Guard") : TEXT("Failed Guard"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, DotResult < 0.f ? FColor::Green : FColor::Red, GuardValid);

	// ���ֺ��� ������ true
	return DotResult < -0.1f;
}

bool UEosFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UEosAbilitySystemComponent* SourceASC = GetNativeEosAbilitySystemComponent(InInstigator);
	UEosAbilitySystemComponent* TargetASC = GetNativeEosAbilitySystemComponent(InTargetActor);

	// ���� �ڵ�� Ÿ�ٿ� ����Ʈ �ߵ��ϰ� �ڵ� ����
	FActiveGameplayEffectHandle ApplyGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	// ����Ʈ ���� ���� ��ȯ
	return ApplyGameplayEffectHandle.WasSuccessfullyApplied();
}

FGameplayTag UEosFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InReacter, float& OutAngleDiffrence)
{
	check(InAttacker && InReacter);
	// ����� ���� ����
	const FVector ReacterForward = InReacter->GetActorForwardVector();
	// ������ ��ġ�� ���ϴ� ���� ���� ���
	const FVector ReacterNormalized = (InAttacker->GetActorLocation() - ReacterForward).GetSafeNormal();
	
	// ���� ���
	const float DotResult = FVector::DotProduct(ReacterForward, ReacterNormalized);
	// ���� ȯ��
	OutAngleDiffrence = UKismetMathLibrary::DegAcos(DotResult);
	// ���� ���
	const FVector CrossResult = FVector::CrossProduct(ReacterForward, ReacterNormalized);

	if (CrossResult.Z < 0.f)
	{
		// ������ ������ ���
		OutAngleDiffrence *= -1.f;
	}

	if (OutAngleDiffrence >= -45.f && OutAngleDiffrence < 45.f)
	{
		return EosGameplayTags::Common_Status_HitReact_Front;
	}
	else if (OutAngleDiffrence < -45.f && OutAngleDiffrence >= -135.f)
	{
		return EosGameplayTags::Common_Status_HitReact_Left;
	}
	else if (OutAngleDiffrence > 45.f || OutAngleDiffrence <= 135.f)
	{
		return EosGameplayTags::Common_Status_HitReact_RIght;
	}
	else if (OutAngleDiffrence < -135.f || OutAngleDiffrence > 135.f)
	{
		return EosGameplayTags::Common_Status_HitReact_Back;
	}

	return EosGameplayTags::Common_Status_HitReact_Front;
}

bool UEosFunctionLibrary::CheckTargetIsEnemy(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
	// �� ���� ��ȯ
	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

bool UEosFunctionLibrary::CheckTextLength(const FString InString, int32 MinLength, int32 MaxLength)
{
	if (InString.Len() > MinLength && InString.Len() <= MaxLength)
		return true;
	return false;
}
