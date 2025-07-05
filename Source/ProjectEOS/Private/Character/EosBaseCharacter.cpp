// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EosBaseCharacter.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"
#include "AbilitySystem/EosAttributeSet.h"
#include "DataAssets/InitializeData/EosDataAsset_BaseStartUpData.h"
#include "MotionWarpingComponent.h"
#include "Managers/EosBaseBossIntroManager.h"
#include "Kismet/GameplayStatics.h"

// �⺻�� ���� �� �ֿ� ������Ʈ �ʱ�ȭ
AEosBaseCharacter::AEosBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->bReceivesDecals = false;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->bEnableUpdateRateOptimizations = false;

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* AEosBaseCharacter::GetAbilitySystemComponent() const
{
	return GetEosAbilitySystemComponent();
}

// Called when the game starts or when spawned
void AEosBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(BossIntroManager)
	{
		// �ƾ� ���� ��������Ʈ ���ε�
		BossIntroManager->OnFinishedScene.AddDynamic(this, &ThisClass::OnCutSceneFinished);
	}
	// ��ġ�� ��Ʈ�� �Ŵ��� ����
	BossIntroManager = Cast<AEosBaseBossIntroManager>(UGameplayStatics::GetActorOfClass(GetWorld(), BossIntroManagerClass));
}

void AEosBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// Called every frame
void AEosBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEosBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UEosBaseCombatComponent* AEosBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

void AEosBaseCharacter::OnCutSceneFinished()
{
}
