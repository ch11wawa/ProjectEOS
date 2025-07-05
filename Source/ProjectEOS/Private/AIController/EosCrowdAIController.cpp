// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/EosCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

AEosCrowdAIController::AEosCrowdAIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFallowingComponent")))
{
	// Sense Config 설정
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfigSight"));
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfigSight->SightRadius = 1000.f;
	AISenseConfigSight->LoseSightRadius = 0.f;
	AISenseConfigSight->PeripheralVisionAngleDegrees = 360.f;

	// Perception 기본 값 설정
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	// 팀 설정
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AEosCrowdAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// 조건 검사용 폰
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	// 비교자 팀 저장
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());
	// 팀 비교
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		// 적
		return ETeamAttitude::Hostile;
	}
	// 아군
	return ETeamAttitude::Friendly;
}

void AEosCrowdAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UCrowdFollowingComponent* CrowdComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		// 군중 시뮬레이션 레벨 지정
		CrowdComponent->SetCrowdSimulationState(bEnabledDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidanceQuality)
		{
		case 1 :
			CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2 :
			CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;
		}
		// 군중 옵션 초기화
		CrowdComponent->SetAvoidanceGroup(1);
		CrowdComponent->SetGroupsToAvoid(1);
		CrowdComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void AEosCrowdAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		// 타겟이 없을 때만 타겟 설정
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			// 감각 감지 시 타겟 설정
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
			}
		}
	}
}