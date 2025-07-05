// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "EosBaseBossIntroManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishedScene);

class UBoxComponent;
class ULevelSequence;
class AEosBasePlayerCharacter;
class ULevelSequencePlayer;
class ALevelSequenceActor;

UCLASS()
class PROJECTEOS_API AEosBaseBossIntroManager : public AActor
{
	GENERATED_BODY()

/// ENGINE FUNCTION	
public:	
	AEosBaseBossIntroManager();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

/// CUSTOM FUNCTION
protected:
	void PlayBattleBGM();
	void LockPlayerInput(bool bShouldLock);
	void BindAllPlayerToSequence();
	void RemoveNotUsedDummys();
	void RemoveAllDummys();
	void VisibleDummys();
	void PlaySequence();
	UFUNCTION()
	void FinishedScene();

/// CUSTOM VARIABLE
public:
	UPROPERTY(BlueprintAssignable)
	FOnFinishedScene OnFinishedScene;

	UPROPERTY(VisibleAnywhere, Category = "Trigger")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditDefaultsOnly, Category = "Sequence")
	ULevelSequence* IntroSequence;

	UPROPERTY(VisibleAnywhere, Category = "Player")
	AEosBasePlayerCharacter* PlayerCharacter;

	UPROPERTY()
	ULevelSequencePlayer* SequencePlayer;

	UPROPERTY()
	ALevelSequenceActor* SequenceActor;

	UPROPERTY(EditDefaultsOnly, Category = "Sequence")
	UAudioComponent* BattleBGMComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sequence")
	USoundBase* BattleBGM;

	FTimerHandle BattleBGMTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Sequence")
	float BattleBGMStartTime = 0.f;

	bool bHasPlayed = false;
};
