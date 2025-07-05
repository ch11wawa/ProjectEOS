// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/EosBaseBossIntroManager.h"
#include "Components/BoxComponent.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "MovieSceneSequencePlayer.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tracks/MovieSceneSkeletalAnimationTrack.h"

AEosBaseBossIntroManager::AEosBaseBossIntroManager()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	RootComponent = TriggerBox;
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	BattleBGMComp = CreateDefaultSubobject<UAudioComponent>("BattleBGM");
}

void AEosBaseBossIntroManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEosBaseBossIntroManager::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bHasPlayed && OtherActor && OtherActor->IsA<AEosBasePlayerCharacter>())
	{
		bHasPlayed = true;
		if (BattleBGMComp)
		{
			// Battle BGM Ÿ�̹� ����
			if (!GetWorld()->GetTimerManager().IsTimerActive(BattleBGMTimerHandle))
			{
				GetWorld()->GetTimerManager().SetTimer(BattleBGMTimerHandle, this, &ThisClass::PlayBattleBGM, BattleBGMStartTime, false);
			}
		}
		if (IntroSequence && !SequencePlayer)
		{
			// ������ ����
			FMovieSceneSequencePlaybackSettings Settings;
			Settings.bAutoPlay = false;
			Settings.bDisableLookAtInput = true;
			Settings.bDisableMovementInput = true;
			Settings.bHideHud = true;

			// ���� ������ ����
			SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), IntroSequence, Settings, SequenceActor);
			if (SequencePlayer)
			{
				// ������ ���� ���ε�
				SequencePlayer->OnFinished.AddDynamic(this, &ThisClass::FinishedScene);
				// �÷��̾� ���̿� ���ε�
				BindAllPlayerToSequence();
				// ���� ����
				VisibleDummys();
				// �̻�� ���� ����
				RemoveNotUsedDummys();
				// ������ ���
				GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::PlaySequence);
				// ��� ���� ����
				RemoveAllDummys();
			}
		}
	}
}

void AEosBaseBossIntroManager::PlayBattleBGM()
{
	GetWorld()->GetTimerManager().ClearTimer(BattleBGMTimerHandle);
	BattleBGMComp = UGameplayStatics::SpawnSound2D(GetWorld(), BattleBGM);
}

void AEosBaseBossIntroManager::LockPlayerInput(bool bShouldLock)
{
}

void AEosBaseBossIntroManager::BindAllPlayerToSequence()
{
	if (!SequenceActor || !IntroSequence) return;

	ULevelSequence* Sequence = Cast<ULevelSequence>(IntroSequence);
	if (!Sequence) return;

	const int32 MaxPlayers = 4;
	// �ִ� �÷��̾� ��ȸ
	for (int32 i = 0; i < MaxPlayers; ++i)
	{
		// �±׷� ���� ȣ��
		FString TagName = FString::Printf(TEXT("Player%d"), i + 1);
		FMovieSceneObjectBindingID BindingID = SequenceActor->GetSequence()->FindBindingByTag(*TagName);

		if (!BindingID.IsValid()) continue;
		
		// ĳ���� ȣ��
		ACharacter* CurrentPlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, i);

		if (!CurrentPlayerCharacter) continue;

		// ���̿� �÷��̾� ���ε�
		SequenceActor->SetBindingByTag(*TagName, { CurrentPlayerCharacter });

		//AEosBasePlayerCharacter* EosBasePlayerCharacter = Cast<AEosBasePlayerCharacter>(CurrentPlayerCharacter);
		//if(EosBasePlayerCharacter)
		//{
		//	FGuid BindingGuid = BindingID.GetGuid();
		//	if (!BindingGuid.IsValid()) return;

		//	TArray<UMovieSceneTrack*> Tracks = Sequence->GetMovieScene()->FindTracks(UMovieSceneSkeletalAnimationTrack::StaticClass(), BindingGuid);
		//	
		//	for (UMovieSceneTrack* Track : Tracks)
		//	{
		//		if (auto* AnimTrack = Cast<UMovieSceneSkeletalAnimationTrack>(Track))
		//		{
		//			TArray<UMovieSceneSection*> Sections = AnimTrack->GetAllSections();
		//			
		//			for (auto* Section : Sections)
		//			{
		//				if (UMovieSceneSkeletalAnimationSection* AnimSection = Cast<UMovieSceneSkeletalAnimationSection>(Section))
		//				{
		//					AnimSection->Modify();
		//					AnimSection->Params.Animation = EosBasePlayerCharacter->CinematicIdleAnim;
		//					AnimSection->MarkAsChanged();
		//				}
		//			}
		//		}
		//	}
		//}
	}
}

void AEosBaseBossIntroManager::RemoveNotUsedDummys()
{
	TArray<AActor*> DummyActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("SequencerActor"), DummyActors);
	// �ʰ� ���̴� ����
	int32 PlayerCount = UGameplayStatics::GetNumPlayerControllers(GetWorld());
	for (int i = PlayerCount; i < DummyActors.Num(); ++i)
	{
		if (AActor* DummyActor = DummyActors[i])
		{
			DummyActor->Destroy();
		}
	}
}

void AEosBaseBossIntroManager::RemoveAllDummys()
{
	// ��� ���̴� ����
	TArray<AActor*> DummyActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("SequencerActor"), DummyActors);

	for (int i = 0; i < DummyActors.Num(); ++i)
	{
		if (AActor* DummyActor = DummyActors[i])
		{
			DummyActor->Destroy();
		}
	}
}

void AEosBaseBossIntroManager::VisibleDummys()
{
	// ���� ����
	TArray<AActor*> DummyActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("SequencerActor"), DummyActors);

	int32 PlayerCount = UGameplayStatics::GetNumPlayerControllers(GetWorld());

	for (int i = 0; i < PlayerCount; ++i)
	{
		if (AActor* DummyActor = DummyActors[i])
		{
			DummyActor->SetActorHiddenInGame(false);
		}
	}
}

void AEosBaseBossIntroManager::PlaySequence()
{
	SequencePlayer->Play();
}

void AEosBaseBossIntroManager::FinishedScene()
{
	OnFinishedScene.Broadcast();
}