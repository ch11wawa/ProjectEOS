// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController/EosCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

AEosCrowdAIController::AEosCrowdAIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFallowingComponent")))
{
	// Sense Config ����
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfigSight"));
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfigSight->SightRadius = 1000.f;
	AISenseConfigSight->LoseSightRadius = 0.f;
	AISenseConfigSight->PeripheralVisionAngleDegrees = 360.f;

	// Perception �⺻ �� ����
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	// �� ����
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AEosCrowdAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// ���� �˻�� ��
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	// ���� �� ����
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());
	// �� ��
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		// ��
		return ETeamAttitude::Hostile;
	}
	// �Ʊ�
	return ETeamAttitude::Friendly;
}

void AEosCrowdAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UCrowdFollowingComponent* CrowdComponent = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		// ���� �ùķ��̼� ���� ����
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
		// ���� �ɼ� �ʱ�ȭ
		CrowdComponent->SetAvoidanceGroup(1);
		CrowdComponent->SetGroupsToAvoid(1);
		CrowdComponent->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

void AEosCrowdAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		// Ÿ���� ���� ���� Ÿ�� ����
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			// ���� ���� �� Ÿ�� ����
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
			}
		}
	}
}