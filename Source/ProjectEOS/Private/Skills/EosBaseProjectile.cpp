// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/EosBaseProjectile.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EosFunctionLibrary.h"
#include "EosGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AEosBaseProjectile::AEosBaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);

	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());
	ProjectileNiagaraComponent->SetAutoActivate(false);

	ProjectileParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticleComponent"));
	ProjectileParticleComponent->SetupAttachment(GetRootComponent());
	ProjectileParticleComponent->SetAutoActivate(true);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 700.f;
	ProjectileMovementComponent->MaxSpeed = 900.f;
	ProjectileMovementComponent->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AEosBaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileReactPolicy == EProjectileReactPolicy::OnBeginOverlap)
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	
}

// Called every frame
void AEosBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEosBaseProjectile::SetOwnerIgnoreCollision(AActor* InOwner)
{
	if (UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		if (InOwner)
		{
			RootComp->IgnoreActorWhenMoving(InOwner, true);
		}
	}
}

void AEosBaseProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Ÿ�� �� VFX ����
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);

	APawn* HitPawn = Cast<APawn>(OtherActor);
	// �� üũ
	if (!HitPawn || !UEosFunctionLibrary::CheckTargetIsEnemy(GetInstigatorController()->GetPawn(), HitPawn))
	{
		Destroy();
		return;
	}

	// ���� ���� ����
	bool bIsValidGuard = false;
	const bool bIsPlayerGuard = UEosFunctionLibrary::NativeDoesActorHaveTag(OtherActor, EosGameplayTags::Player_Status_Guarding);

	// ���� ��, ���� ��ȿ�� ����
	if (bIsPlayerGuard)
	{
		bIsValidGuard = UEosFunctionLibrary::IsValidGuard(GetInstigator(), OtherActor);
	}
	FGameplayEventData Data;
	Data.Instigator = GetInstigator();
	Data.Target = HitPawn;

	// ������ ��ȿ�ϸ� ���� ���� �߽�
	if (bIsValidGuard)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
		(
			HitPawn,
			EosGameplayTags::Player_Event_GuardSuccess,
			Data
		);
	}

	// ��ȿ���� ������ ����� ó��
	else
	{
		HandleApplyProjectileDamage(HitPawn, Data);
	}

	// �ı�
	Destroy();
}

void AEosBaseProjectile::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AEosBaseProjectile::SetDamageEffectSpecHandle(const FGameplayEffectSpecHandle& InSpecHandle)
{
	if (!HasAuthority()) return;

	if (!InSpecHandle.IsValid()) return;

	ProjectileDamageEffectSpecHandle = InSpecHandle;
}

void AEosBaseProjectile::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	//checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Forgot spec handle to projectiles Check Blueprints %s"), *GetActorNameOrLabel());
	if (!HasAuthority()) return; // ���� ����

	if (!ProjectileDamageEffectSpecHandle.IsValid()) return;

	// 
	const bool bWasApplied = UEosFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);
	
	if (bWasApplied)
	{
		switch (ProjectileReactTypePolicy)
		{
		case EProjectileReactTypePolicy::LightReact:
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
			(
				InHitPawn,
				EosGameplayTags::Common_Event_HitReact_Light,
				InPayload
			);
			break;
		case EProjectileReactTypePolicy::HeavyReact:
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
			(
				InHitPawn,
				EosGameplayTags::Common_Event_HitReact_Heavy,
				InPayload
			);
			break;
		}

	}
}