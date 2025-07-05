// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EosPlayerGameplayAbility.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "PlayerController/EosBasePlayerController.h"
#include "Items/Weapon/EosBaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"
#include "EosGameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "EosFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameplayAbilityBlueprint.h"
#include "AbilitySystemBlueprintLibrary.h"

void UEosPlayerGameplayAbility::Client_ApplyDash_Implementation()
{
	ApplyDash();
}

void UEosPlayerGameplayAbility::Server_GetLastInputAndUpdateRotationForDash_Implementation()
{
	ApplyDash();
	Client_ApplyDash();
}

void UEosPlayerGameplayAbility::Server_GetLastInputAndUpdateRotationForAttack_Implementation(FVector InCachedLastDirection)
{
	// ���� ���� ����
	CachedLastDirection = InCachedLastDirection;

	// ���� Ű, ���� �����̼� ����
	const FName WarpKey = FName(TEXT("AttackDirection"));
	FRotator RotFromX = UKismetMathLibrary::MakeRotFromX(InCachedLastDirection);

	// ���� ���� ����
	GetPlayerCharacterFromActorInfo()->Server_AddOrUpdateWarpTargetfromLocationandRotation(WarpKey, FVector::ZeroVector, RotFromX);
}

void UEosPlayerGameplayAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UEosPlayerGameplayAbility, CachedBasePlayerCharacter);
	DOREPLIFETIME(UEosPlayerGameplayAbility, CachedBasePlayerController);
	DOREPLIFETIME(UEosPlayerGameplayAbility, CachedLastDirection);
}

AEosBasePlayerCharacter* UEosPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if(!CachedBasePlayerCharacter.IsValid())
	{
		CachedBasePlayerCharacter = Cast<AEosBasePlayerCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedBasePlayerCharacter.IsValid() ? CachedBasePlayerCharacter.Get() : nullptr;
}

AEosBasePlayerController* UEosPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedBasePlayerController.IsValid())
	{
		CachedBasePlayerController = Cast<AEosBasePlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedBasePlayerController.IsValid() ? CachedBasePlayerController.Get() : nullptr;
}

UEosPlayerCombatComponent* UEosPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

// �÷��̾� ����� ��� ���� �ڵ� ����
FGameplayEffectSpecHandle UEosPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);
	// ���ؽ�Ʈ �ڵ� ����
	FGameplayEffectContextHandle ContextHandle = GetEosAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	// ���� �ڵ� ����
	FGameplayEffectSpecHandle EffectSpecHandle = GetEosAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec
	(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	// SetByCaller�� �±׿� ������� Map���·� ����
	EffectSpecHandle.Data->SetSetByCallerMagnitude
	(
		EosGameplayTags::Common_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);

	// SetByCaller�� �±׿� �޺� ���� Map���·� ����
	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude
		(
			InCurrentAttackTypeTag,
			InUsedComboCount
		);
	}
	// �ڵ� ����ü�� ��ȯ
	return EffectSpecHandle;
}

FGameplayEffectSpecHandle UEosPlayerGameplayAbility::MakeSkillDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InSkillDamage, FGameplayTag InCurrentAttackTypeTag)
{
	check(EffectClass);

	// ���ؽ�Ʈ �ڵ� ����
	FGameplayEffectContextHandle ContextHandle = GetEosAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	// ����Ʈ �����ڵ� ����
	FGameplayEffectSpecHandle EffectSpecHandle = GetEosAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec
	(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	// �±׿� ����� ��Ī
	EffectSpecHandle.Data->SetSetByCallerMagnitude
	(
		InCurrentAttackTypeTag,
		InSkillDamage
	);

	// ����Ʈ �����ڵ� ��ȯ
	return EffectSpecHandle;
}

void UEosPlayerGameplayAbility::ConsumeDirectionInput()
{
	// ���� ���� ����
	if(UEosFunctionLibrary::IsListenServer(GetWorld()))
	{
		// ȣ��Ʈ ����
		if (GetPlayerCharacterFromActorInfo()->HasAuthority())
		{
			if(IsLocallyControlled())
			{
				// ������ ��ǲ ������ �޾Ƽ� ���� ����
				Server_GetLastInputAndUpdateRotationForAttack(GetValidNormalizeInputVector());
			}
		}
	}
	else
	{
		// Ŭ���̾�Ʈ ����
		if (!GetPlayerCharacterFromActorInfo()->HasAuthority())
		{
			// �����̼� ��û
			Server_GetLastInputAndUpdateRotationForAttack(GetValidNormalizeInputVector());
		}
	}
}

void UEosPlayerGameplayAbility::ComputeDashDirectionAndDistance()
{
	// ���� ���� ����
	if (UEosFunctionLibrary::IsListenServer(GetWorld()))
	{
		// ȣ��Ʈ ����
		if (GetPlayerCharacterFromActorInfo()->HasAuthority())
		{
			if (IsLocallyControlled())
			{
				// ������ ��ǲ ������ �޾Ƴ��� ��� ����
				CachedLastDirection = GetValidNormalizeInputVector();
				ApplyDash();
			}
		}
	}
	else
	{
		if (!GetPlayerCharacterFromActorInfo()->HasAuthority())
		{
			// ��� ��û
			Server_GetLastInputAndUpdateRotationForDash();		
		}
	}
}

void UEosPlayerGameplayAbility::ApplyDash()
{
	// ���� & �������Ű ����
	const FName WarpKey = FName(TEXT("DashDirection"));
	FPredictionKey PredKey = GetCurrentActivationInfo().GetActivationPredictionKey();

	// �ڵ� ���� (���¹̳� ����Ʈ)
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CostControlEffectClass, GetAbilityLevel());

	// �±� �ڽ�Ʈ ����
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
		SpecHandle,
		EosGameplayTags::Player_SetByCaller_Status_Stamina,
		DashCost
	);

	// ASC ����
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();

	if (ASC && SpecHandle.IsValid())
	{
		// ����Ʈ �ߵ� �� �ڵ� ����
		FActiveGameplayEffectHandle ActiveHandle = ASC->ApplyGameplayEffectSpecToSelf
		(
			*SpecHandle.Data.Get(),
			PredKey
		);
		// Sequence 2. ���� ����
		FRotator RotFromX = UKismetMathLibrary::MakeRotFromX(GetValidNormalizeInputVector());
		GetPlayerCharacterFromActorInfo()->Server_AddOrUpdateWarpTargetfromLocationandRotation(WarpKey, FVector::ZeroVector, RotFromX);

		// Sequence 3. �Ÿ� ���� (Ʈ���̽�)
		if (GetPlayerCharacterFromActorInfo()->HasAuthority())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), FString(TEXT("DashSuccess")));
			FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
			float CurrentDashData = UEosFunctionLibrary::GetScalableFloatValueAtLevel(DashData, GetAbilityLevel());

			FVector DashDistanceFromActorLoc = (CachedLastDirection * CurrentDashData) + PlayerLocation;
			FVector UpVectorToDashDist = GetPlayerCharacterFromActorInfo()->GetActorUpVector() * -1.f * TraceDistance;
			//UE_LOG(LogTemp, Warning, TEXT("UpVectorToDashDist = %s"), *UpVectorToDashDist.ToString());

			FVector EndPoint = UpVectorToDashDist + DashDistanceFromActorLoc;

			UWorld* World = GetWorld();

			// ��ðŸ� �Ǻ� ���� Ʈ���̽�
			if (World)
			{
				FHitResult HitResult;
				bool bHit = World->LineTraceSingleByObjectType
				(
					HitResult,
					DashDistanceFromActorLoc,
					EndPoint,
					ECC_WorldStatic
				);
				if (bHit)
				{
					// ��Ʈ ��ġ�� ����
					GetPlayerCharacterFromActorInfo()->Server_AddOrUpdateWarpTargetfromLocation(HitResult.ImpactPoint);
				}
				else
				{
					// ��Ʈ�� ������ ���� ��Ȱ��ȭ
					const FName DashDistance = FName(TEXT("DashDistance"));
					GetPlayerCharacterFromActorInfo()->Server_RemoveWarpTarget(DashDistance);
				}
			}
		}
	}
}

FVector UEosPlayerGameplayAbility::GetValidNormalizeInputVector()
{
	// ������ �Է� ���� ����
	FVector LastInputVector = GetPlayerCharacterFromActorInfo()->GetLastMovementInputVector();
	
	// ����ȭ
	FVector LastInputNorm = LastInputVector.GetSafeNormal(0.0001);
	
	// �Է� ���� ����
	if (FVector::ZeroVector != LastInputNorm)
	{
		// ����ȭ�� ���� ���� ��ȯ
		return LastInputNorm;
	}
	else
	{
		// ���Է� �� ���� ���� ��ȯ
		return GetCurrentForwardVector();
	}
}

FVector UEosPlayerGameplayAbility::GetCurrentForwardVector()
{
	// ���� ���� ��ȯ
	return GetPlayerCharacterFromActorInfo()->GetActorForwardVector();
}

void UEosPlayerGameplayAbility::SelectWeaponAttachment(USkeletalMeshComponent* InSkeletalMesh, AEosBaseWeapon* InFoundWeapon)
{
	if(InFoundWeapon)
	{
		// ����ġ �ɼ� ����
		FAttachmentTransformRules AttachmentRules
		(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative,
			EAttachmentRule::KeepWorld,
			false
		);

		// ���� Ÿ�� �����ͼ� Type�� ����ġ
		switch(InFoundWeapon->WeaponEquipType)
		{
		// �޼�
		case EWeaponEquipType::LeftHand : 
			// ��ƼŬ ���� ���� ����
			if(InFoundWeapon->bIsParticleWeapon)
			{
				const FName& Socket = FName(TEXT("Weapon_L"));
				GetPlayerCharacterFromActorInfo()->Multicast_SpawnWeaponParticleL(InSkeletalMesh, InFoundWeapon, Socket);
			}
			InFoundWeapon->AttachToComponent
			(
				InSkeletalMesh,
				AttachmentRules,
				"Weapon_L"
			);
			break;

		// ������
		case EWeaponEquipType::RightHand :
			// ��ƼŬ ���� ���� ����
			if (InFoundWeapon->bIsParticleWeapon)
			{
				const FName& Socket = FName(TEXT("Weapon_R"));
				GetPlayerCharacterFromActorInfo()->Multicast_SpawnWeaponParticleR(InSkeletalMesh, InFoundWeapon, Socket);
			}
			InFoundWeapon->AttachToComponent
			(
				InSkeletalMesh,
				AttachmentRules,
				"Weapon_R"
			);
			break;

		// ���
		case EWeaponEquipType::TwoHands:
			// ��ƼŬ ���� ���� ����
			if (InFoundWeapon->bIsParticleWeapon)
			{
				const FName& SocketL = FName(TEXT("Weapon_L"));
				GetPlayerCharacterFromActorInfo()->Multicast_SpawnWeaponParticleL(InSkeletalMesh, InFoundWeapon, SocketL);
				const FName& SocketR = FName(TEXT("Weapon_R"));
				GetPlayerCharacterFromActorInfo()->Multicast_SpawnWeaponParticleSubR(InSkeletalMesh, InFoundWeapon, SocketR);
			}
			InFoundWeapon->AttachToComponent
			(
				InSkeletalMesh,
				AttachmentRules,
				"Weapon_L"
			);
			InFoundWeapon->SubWeaponMesh->AttachToComponent
			(
				InSkeletalMesh,
				AttachmentRules,
				"Weapon_R"
			);
			break;
		}
	}
}
