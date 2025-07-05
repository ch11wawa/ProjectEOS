// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Struct/EosPlayerInfo.h"
#include "EosGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	

public:
	UFUNCTION(BlueprintCallable)
	FPlayerInfo GetPlayerInfo() { 
		return PlayerInfo; }

	UFUNCTION()
	void SetPlayerGuid(const FGuid NewGuid) { PlayerInfo.PlayerGUID = NewGuid; }

	UFUNCTION(BlueprintCallable)
	FGuid GetPlayerGuid() const { return PlayerInfo.PlayerGUID; }

	UFUNCTION()
	FString GetNickName() const { return PlayerInfo.NickName; }

	UFUNCTION(BlueprintCallable)
	EPlayerClassType GetCharacterClass() const { return PlayerInfo.CharacterClass; }

	UFUNCTION()
	void SetPlayerClass(EPlayerClassType NewPlayerClass) { PlayerInfo.CharacterClass = NewPlayerClass; 		
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("%d"), PlayerInfo.CharacterClass));

	}

	UFUNCTION()
	void SetNickName(FString NewNickName) { PlayerInfo.NickName = NewNickName; }

	UFUNCTION(BlueprintCallable)
	TArray<FPlayerInfo> GetPartyList();

	UFUNCTION()
	void SetPartyList(TArray<FPlayerInfo> NewPartyArr);

	UFUNCTION()
	FString GetHostIP() const { return HostIP; }

	UFUNCTION()
	void SetHostIP(const FString NewHostIP) { HostIP = NewHostIP; }

	void MoveLevel(FString& LevelName);
	void MoveLevel(FString& LevelName, FString& Option);

private:
	UPROPERTY()
	FPlayerInfo PlayerInfo;

	UPROPERTY()
	TArray<FPlayerInfo> PartyArr;

	UPROPERTY()
	FString HostIP;
};
