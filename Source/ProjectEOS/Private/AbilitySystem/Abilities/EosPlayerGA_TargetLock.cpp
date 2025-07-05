// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/EosPlayerGA_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "Widget/EosBaseWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "PlayerController/EosBasePlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "EosFunctionLibrary.h"
#include "EosGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemBlueprintLibrary.h"

void UEosPlayerGA_TargetLock::Server_RequestRotationControl_Implementation (AEosBasePlayerCharacter* InRotateCharacter, FRotator TargetRot)
{
	// �����̼� ����
	InRotateCharacter->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	// Ŭ���̾�Ʈ�� ���û
	Client_RequestRotationControl(InRotateCharacter, TargetRot);
}

void UEosPlayerGA_TargetLock::Client_RequestRotationControl_Implementation(AEosBasePlayerCharacter* InRotateCharacter, FRotator TargetRot)
{
	// �����̼� ����
	InRotateCharacter->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
}

void UEosPlayerGA_TargetLock::Server_RequestInitTargetLockMovement_Implementation(UCharacterMovementComponent* InMovementComp)
{
	// ���� �̵��ӵ� ����
	CachedDefaultMaxWalkSpeed = InMovementComp->MaxWalkSpeed;
	if(IsLocallyControlled())
	{
		if(GetAvatarActorFromActorInfo()->HasAuthority())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Walk : %f"), CachedDefaultMaxWalkSpeed));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Walk : %f"), CachedDefaultMaxWalkSpeed));
		}
	}
	// ���ڸ�� Ȱ��ȭ�ϰ� �̵��ӵ� ����
	InMovementComp->bOrientRotationToMovement = false;
	InMovementComp->MaxWalkSpeed = TargetLockMaxWalkSpeed;
	// Ŭ�� ���� ���� ��û
	Client_RequestInitTargetLockMovement(InMovementComp);
}

void UEosPlayerGA_TargetLock::Client_RequestInitTargetLockMovement_Implementation(UCharacterMovementComponent* InMovementComp)
{
	// ���ڸ�� Ȱ��ȭ�ϰ� �̵��ӵ� ����

	InMovementComp->bOrientRotationToMovement = false;
	InMovementComp->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void UEosPlayerGA_TargetLock::Server_RequestResetTargetLockMovement_Implementation(UCharacterMovementComponent* InResetCharacter)
{
	// �̵��ӵ� ���󺹱� �� ���ڸ�� ��Ȱ��ȭ

	InResetCharacter->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	InResetCharacter->bOrientRotationToMovement = true;
}

void UEosPlayerGA_TargetLock::Server_RequestResetDefaultWalkSpeed_Implementation()
{
	CachedDefaultMaxWalkSpeed = 0.f;
}

void UEosPlayerGA_TargetLock::Server_RequestCheckEnemyStatus_Implementation(AActor* CurrentTarget)
{
	// �������� �±� üũ
	if(!CurrentTarget || UEosFunctionLibrary::NativeDoesActorHaveTag(CurrentTarget, EosGameplayTags::Common_Status_Dead))
	{
		// �׾����� Ŭ���̾�Ʈ�� ����
		Client_RequestCheckEnemyStatus();
		return;
	}
}

void UEosPlayerGA_TargetLock::Client_RequestCheckEnemyStatus_Implementation()
{
	// �����Ƽ ���
	CancelTargetLockAbility();
}

void UEosPlayerGA_TargetLock::Server_RequestCheckEnemyStatusForTryLockOnTarget_Implementation(AActor* CurrentTarget)
{
	// ��� ���� ����
	if (!CurrentTarget || UEosFunctionLibrary::NativeDoesActorHaveTag(CurrentTarget, EosGameplayTags::Common_Status_Dead))
	{
		// Ŭ�󿡼� ��� ó��
		Client_RequestCheckEnemyStatus();
		return;
	}
	else
	{
		// Ŭ�� Ÿ�� ���� ��û
		Client_RequestCheckEnemyStatusForTryLockOnTarget();
	}
}

void UEosPlayerGA_TargetLock::Client_RequestCheckEnemyStatusForTryLockOnTarget_Implementation()
{
	// ���� ����
	LockOnTarget();
	// �����Ʈ ����
	InitTargetLockMovement();
	// ���ؽ�Ʈ �ο�
	InitTargetLockContext();
}

void UEosPlayerGA_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// ���� �õ�
	TryLockOnTarget();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UEosPlayerGA_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// �̵� ���� ���� ���󺹱�
	ResetTargetLockMovement();
	// ���ؽ�Ʈ ȸ��
	ResetTargetLockContext();
	// ������ ���� ��� �ʱ�ȭ
	CleanUp();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UEosPlayerGA_TargetLock::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UEosPlayerGA_TargetLock, CachedDefaultMaxWalkSpeed);
}

void UEosPlayerGA_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if(!GetAvatarActorFromActorInfo()->HasAuthority())
	{
		// ������ ���� �� ��� ���� ����
		Server_RequestCheckEnemyStatus(CurrentLockedActor);
		// ������ �� ��ġ�� ����
		SetTargetLockWidgetPosition();
	}
	else
	{
		// �� ��� ���� ����
		if(IsLocallyControlled())
		{
			if (!CurrentLockedActor || UEosFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, EosGameplayTags::Common_Status_Dead))
			{
				CancelTargetLockAbility();
				return;
			}
			// ������ �� ��ġ�� ����
			SetTargetLockWidgetPosition();
		}
	}
	// �÷��̾� ȸ�� ���� ����
	const bool bShouldOverrideRotation = !UEosFunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), EosGameplayTags::Player_Status_Dash);

	if (bShouldOverrideRotation)
	{
		// �ٶ󺸴� ȸ�� �� ����
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetPlayerCharacterFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());
		
		// ī�޶� ������ ����
		LookAtRot -= FRotator(CameraOffsetDistance, 0.f, 0.f);

		// ��Ʈ�ѷ� ȸ���� �����̼� ���� ��
		const FRotator CurrentControlRot = PC->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLookRotationInterpSpeed);
		
		// ȣ��Ʈ ����
		if(GetAvatarActorFromActorInfo()->HasAuthority())
		{
			if(IsLocallyControlled())
			{
				// ���ʹ� �������� �����̼� ���� ����
				PC->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
				GetPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
			}
		}
		// Ŭ���̾�Ʈ
		else
		{
			AEosBasePlayerCharacter* RequestCharacter = GetPlayerCharacterFromActorInfo();
			// ������ ȸ�� ���� ��û
			Server_RequestRotationControl(RequestCharacter, TargetRot);
			PC->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		}
	}
}

void UEosPlayerGA_TargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	// Ʈ���̽��� Ÿ���� �迭�� ����
	GetAvailableActorsToLock();

	// ��迭 ����
	TArray<AActor* >ActorsOnLeft;
	TArray<AActor* >ActorsOnRight;
	AActor* NewTargetToLock = nullptr;

	// ���ο� Ÿ���� ���� ��/�� �迭 ����
	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	// �������� ��û�� ������ ���� ����� ���� Ÿ���� ����
	if (InSwitchDirectionTag == EosGameplayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	// ������
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}
	// ���ο� Ÿ���� ��ȿ�ϸ� Ÿ�� ��ü
	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

void UEosPlayerGA_TargetLock::TryLockOnTarget()
{
	// ���� ������ ���� Ž��
	GetAvailableActorsToLock();

	// Ž���� ���� �迭�� ������� �����Ƽ ���
	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	// ���� ����� ��ȿ ���� ��ȯ
	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	Server_RequestCheckEnemyStatusForTryLockOnTarget(CurrentLockedActor);
}

void UEosPlayerGA_TargetLock::LockOnTarget()
{
	// Ÿ�ٶ��� ���� ����
	DrawTargetLockWidget();
	// Ÿ�ٶ��� ���� ��ġ ����
	SetTargetLockWidgetPosition();
}

void UEosPlayerGA_TargetLock::GetAvailableActorsToLock()
{
	// �迭 ����
	AvailableActorsToLock.Empty();
	TArray<FHitResult> BoxTraceHits;

	// ��Ƽ �ڽ� Ʈ���̽�
	UKismetSystemLibrary::BoxTraceMultiForObjects
	(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() * GetPlayerCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	// ��Ʈ�� ���͵� �迭�� ����
	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			AvailableActorsToLock.AddUnique(HitActor);
		}
	}
}

AActor* UEosPlayerGA_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	// �÷��̾�� ����� ���� ����
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UEosPlayerGA_TargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsLeft, TArray<AActor*>& OutActorsRight)
{
	// ���� Ÿ�� ���ų� �迭�� ��������� �����Ƽ ���
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	// �÷��̾� ��ġ ����
	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	// ��ȣ ���� ����ȭ�� ���� ���� ����
	const FVector PlayerToCurrentLockedActorNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
	
	// �迭 loop
	for (AActor* FoundTarget : AvailableActorsToLock)
	{
		// Ÿ���� ���ų� ������ ���� ����
		if (!FoundTarget || FoundTarget == CurrentLockedActor) continue;

		// ���ο� Ÿ�ٰ��� ���� ���� ����
		const FVector PlayerToFoundTargetNormalized = (FoundTarget->GetActorLocation() - PlayerLocation).GetSafeNormal();
		// ������ ����
		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentLockedActorNormalized, PlayerToFoundTargetNormalized);
		
		// ����� ���� ��/�� �з�
		if (CrossResult.Z > 0.f)
		{
			OutActorsRight.AddUnique(FoundTarget);
		}
		else
		{
			OutActorsLeft.AddUnique(FoundTarget);
		}
	}
}

void UEosPlayerGA_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UEosPlayerGA_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();

	CurrentLockedActor = nullptr;

	if (TargetLockWidget)
	{
		TargetLockWidget->RemoveFromParent();
	}

	TargetLockWidget = nullptr;

	TargetWidgetLockSize = FVector2D::ZeroVector;

	Server_RequestResetDefaultWalkSpeed();
	CachedDefaultMaxWalkSpeed = 0.f;
}

void UEosPlayerGA_TargetLock::ResetTargetLockMovement()
{
	UCharacterMovementComponent* RequestMovementComp = GetPlayerCharacterFromActorInfo()->GetCharacterMovement();
	if (CachedDefaultMaxWalkSpeed > 0.f)
	{
		// ������ ���󺹱� ��û
		Server_RequestResetTargetLockMovement(RequestMovementComp);
		// �̵��ӵ� ���� �� ���ڸ�� ��Ȱ��ȭ
		RequestMovementComp->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
		RequestMovementComp->bOrientRotationToMovement = true;
	}
}

void UEosPlayerGA_TargetLock::ResetTargetLockContext()
{
	// ��Ʈ�ѷ� ����ġ �� ��ȯ
	if (!GetAvatarActorFromActorInfo()->GetInstigatorController()) return;
	
	// ȣ��Ʈ ����
	else if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		if (IsLocallyControlled())
		{
			// ���ؽ�Ʈ ���ſ� �ʿ��� �Ű����� ����
			PC = Cast<AEosBasePlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController());
			const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

			check(Subsystem);

			// ���� ���ؽ�Ʈ ����
			Subsystem->RemoveMappingContext(TargetLockMappingContext);
		}
	}

	// Ŭ���̾�Ʈ ����
	if (!GetAvatarActorFromActorInfo()->HasAuthority())
	{
		// ���ؽ�Ʈ ���ſ� �ʿ��� �Ű����� ����
		PC = Cast<AEosBasePlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController());
		const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		check(Subsystem);

		// ���� ���ؽ�Ʈ ����
		Subsystem->RemoveMappingContext(TargetLockMappingContext);
	}
}

void UEosPlayerGA_TargetLock::SetTargetLockWidgetPosition()
{
	// ���� Ȥ�� ������ ���Ͱ� ������ �����Ƽ ���
	if (!TargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}
	FVector2D ScreenPosition;
	
	// ���ʹ� ��ġ�� UI ��ǥ��� ��ȯ
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition
	(
		PC,												// ����Ʈ ���� ��Ʈ�ѷ�
		CurrentLockedActor->GetActorLocation(),			// ���忡�� ��ȯ�� ����
		ScreenPosition,									// ��ǥ ��¹��� ����
		true											// �÷��̾� ����Ʈ �� ��� ��ǥ ����
	);

	// ���� �ƹ� ���� �ȴ�� ������
	if (TargetWidgetLockSize == FVector2d::ZeroVector)
	{
		// ���� Ʈ�� ��ȸ
		TargetLockWidget->WidgetTree->ForEachWidget
		(
			[this](UWidget* FoundWidget)
			{
				// ������ �ڽ� ã����
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					// ã�� ������ �ڽ��� ����, ���̸� ����
					TargetWidgetLockSize.X = FoundSizeBox->GetWidthOverride();
					TargetWidgetLockSize.Y = FoundSizeBox->GetHeightOverride();
				}
			}
		);
	}
	// �߾����� �����ϰ� ���� ��ǥ�� ����
	ScreenPosition -= (TargetWidgetLockSize / 2.f);
	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UEosPlayerGA_TargetLock::DrawTargetLockWidget()
{
	// �ڽ��� ��Ʈ�ѷ� �ƴϸ� ��ȯ
	if (!GetActorInfo().IsLocallyControlled()) return;

	PC = Cast<AEosBasePlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController());
	if (!PC)
	{
		// ��Ʈ�ѷ� ĳ��Ʈ ���� �� ��õ�
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UEosPlayerGA_TargetLock::DrawTargetLockWidget);
		return;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), PC));
	}

	if (!TargetLockWidget)
	{
		// ������ ������ ������ �����ϰ� ���
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign TargetLockWidgetClass, Check GA_TargetLock"));
		TargetLockWidget = CreateWidget<UEosBaseWidget>(PC, TargetLockWidgetClass);
		check(TargetLockWidget);
		TargetLockWidget->AddToViewport();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Done Add viewport")));
	}
}

void UEosPlayerGA_TargetLock::InitTargetLockMovement()
{
	UCharacterMovementComponent* RequestMovement = GetPlayerCharacterFromActorInfo()->GetCharacterMovement();
	// ������ �̵� ���� �ʱ�ȭ ��û
	Server_RequestInitTargetLockMovement(RequestMovement);
}

void UEosPlayerGA_TargetLock::InitTargetLockContext()
{
	// ȣ��Ʈ ����
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		if (IsLocallyControlled())
		{
			PC = Cast<AEosBasePlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController());
			const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();

			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

			check(Subsystem);

			// ���� ���ؽ�Ʈ �ο�
			Subsystem->AddMappingContext(TargetLockMappingContext, 3);
		}
	}
	// Ŭ���̾�Ʈ
	if(!GetAvatarActorFromActorInfo()->HasAuthority())
	{
		PC = Cast<AEosBasePlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController());
		const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

		check(Subsystem);

		// ���� ���ؽ�Ʈ �ο�
		Subsystem->AddMappingContext(TargetLockMappingContext, 3);
	}
}