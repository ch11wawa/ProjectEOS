// Fill out your copyright notice in the Description page of Project Settings.


#include "EosGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UEosGameInstance::Init()
{
	/*FGuid NewGUID = FGuid::NewGuid();
	PlayerInfo.PlayerGUID = NewGUID;*/
}

TArray<FPlayerInfo> UEosGameInstance::GetPartyList()
{
	return PartyArr;
}

void UEosGameInstance::SetPartyList(TArray<FPlayerInfo> NewPartyArr)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Instance : %d"), NewPartyArr.Num()));

	PartyArr = NewPartyArr;
}

void UEosGameInstance::MoveLevel(FString& LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName), true);
}

void UEosGameInstance::MoveLevel(FString& LevelName, FString& Option)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName), true, Option);
}
