// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystem/GameState/EosBaseGameState.h"
#include "Net/UnrealNetwork.h"

AEosBaseGameState::AEosBaseGameState()
{
	bReplicates = true;
}

void AEosBaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEosBaseGameState, PartyList);
}
