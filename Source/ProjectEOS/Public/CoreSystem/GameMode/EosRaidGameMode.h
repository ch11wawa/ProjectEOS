// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreSystem/GameMode/EosBaseGameMode.h"
#include "EosRaidGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API AEosRaidGameMode : public AEosBaseGameMode
{
	GENERATED_BODY()
/// ENGINE FUNCTION
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer);

/// CUSTOM FUNCTION
/// CUSTOM VARIABLE
/// GETTER FUNCTION
/// HELPER FUNCTION
public:
	UFUNCTION(BlueprintCallable)
	void SetParty();

	UFUNCTION(Category = "Party")
	void UpdateParty(const FGuid TargetGUID, float NewHP);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnAndPossess();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Party")
	TArray<FPlayerInfo> PartyArr;

	UPROPERTY(BlueprintReadWrite, Category = "Party")
	FTimerHandle PartyUITimer;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	FTimerHandle PlayerSpawnTimer;

public:
	UFUNCTION()
	int32 GetPartyNum() { return PartyArr.Num(); }
};
