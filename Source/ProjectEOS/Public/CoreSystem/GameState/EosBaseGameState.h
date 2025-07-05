// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Struct/EosPlayerInfo.h"
#include "EosBaseGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API AEosBaseGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

private:
	UPROPERTY(Replicated)
	TArray<FPlayerInfo> PartyList;

public:
	AEosBaseGameState();

	UFUNCTION(BlueprintCallable)
	void AddParty(FPlayerInfo NewParty)
	{ 

		PartyList.Add(NewParty); 
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("GameState : %d"), PartyList.Num()));


	}

	UFUNCTION()
	TArray<FPlayerInfo> GetPartyList() { return PartyList; }
	
};
