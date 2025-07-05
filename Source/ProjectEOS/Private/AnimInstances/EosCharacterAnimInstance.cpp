// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/EosCharacterAnimInstance.h"
#include "Character/EosBaseCharacter.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UEosCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AEosBaseCharacter>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
	OwningPlayerCharacter = Cast<AEosBasePlayerCharacter>(TryGetPawnOwner());
}

void UEosCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	// �ӵ�
	Speed = OwningCharacter->GetVelocity().Size2D();
	
	// ������ ���� ����
	bIsAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	// ���� ����
	Direction = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}