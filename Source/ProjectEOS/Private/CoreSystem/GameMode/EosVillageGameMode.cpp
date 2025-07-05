// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystem/GameMode/EosVillageGameMode.h"
#include "CoreSystem/GameMode/EosBaseGameMode.h"
#include "PlayerController/EosWorldPlayerController.h"
#include "CoreSystem/PlayerState/EosBasePlayerState.h"
#include "Struct/EosPlayerInfo.h"

void AEosVillageGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("Villlage OnPostLogin"));
	CurrentPlayer->bIsRaid = false;
	CurrentPlayer->Client_GetGameInstance();
}

void AEosVillageGameMode::CreateParty(const FGuid& HostGUID, const FString& TargetNickName)
{
	FPlayerInfo* HostPlayerInfo = FindPlayerInfoWithGuid(HostGUID);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *HostPlayerInfo->PlayerGUID.ToString());
	if (!HostPlayerInfo) return;

	if (HostPlayerInfo->NickName.Equals(TargetNickName))
	{
		HostPlayerInfo->PlayerController->Client_SystemMessage(FText::FromString("Nice try, but you can't invite yourself!"));
		return;
	}

	if (!HostPlayerInfo->bIsHost && HostPlayerInfo->bIsParty)
	{
		HostPlayerInfo->PlayerController->Client_SystemMessage(FText::FromString("You are already a member of a party."));
		return;
	}

	for (auto& PlayerInfo : PlayerInfoArr)
	{
		if (PlayerInfo.NickName.Equals(TargetNickName))
		{
			if (PlayerInfo.bIsParty || PlayerInfo.bIsHost)
			{
				HostPlayerInfo->PlayerController->Client_SystemMessage(FText::FromString("The player is already in a party."));
				return;
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerInfo.PlayerGUID.ToString());
			FPartyInviteInfo PartyInviteInfo(PlayerInfo.PlayerGUID, false);
			HostPlayerInfo->PartyInviteList.Add(PartyInviteInfo);
			PlayerInfo.PlayerController->Client_AskParty(HostGUID, HostPlayerInfo->NickName);

			FText SystemMessage = FText::Format(FText::FromString("{0} has been invited to your party."), FText::FromString(PlayerInfo.NickName));
			HostPlayerInfo->PlayerController->Client_SystemMessage(SystemMessage);
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *HostPlayerInfo->PlayerGUID.ToString());
			return;
		}
	}
	HostPlayerInfo->PlayerController->Client_SystemMessage(FText::FromString("The player does not exist."));
}

void AEosVillageGameMode::AnswerParty(const FGuid& HostGUID, const FGuid& TargetGUID, const bool bIsParty)
{
	UE_LOG(LogTemp, Warning, TEXT("GM_AnswerParty"));

	FPlayerInfo* HostPlayerInfo = FindPlayerInfoWithGuid(HostGUID);

	if (HostPlayerInfo)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetGUID.ToString());


		for (auto& Target : HostPlayerInfo->PartyInviteList)
		{
			FPlayerInfo* TargetPlayerInfo = FindPlayerInfoWithGuid(Target.TargetGUID);
			if (Target.TargetGUID == TargetGUID)
			{
				Target.bIsParty = bIsParty;

				if (Target.bIsParty)
				{
					HostPlayerInfo->bIsHost = true;
					TargetPlayerInfo->bIsParty = true;
					UE_LOG(LogTemp, Warning, TEXT("Yes Party"));
					HostPlayerInfo->PlayerController->Client_AddPartyList(*TargetPlayerInfo);
					FText SystemMessage = FText::Format(FText::FromString("{0} has joined your party."), FText::FromString(TargetPlayerInfo->NickName));
					HostPlayerInfo->PlayerController->Client_SystemMessage(SystemMessage);
				}
				else
				{
					FText SystemMessage = FText::Format(FText::FromString("{0} has refused the party invite."), FText::FromString(TargetPlayerInfo->NickName));
					HostPlayerInfo->PlayerController->Client_SystemMessage(SystemMessage);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Target"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No HostPlayerInfo"));
	}
}

void AEosVillageGameMode::StartRaid(const FGuid& HostGUID, const FString& HostIP)
{
	FPlayerInfo* HostPlayerInfo = FindPlayerInfoWithGuid(HostGUID);
	for (auto& Party : HostPlayerInfo->PartyInviteList)
	{
		if (Party.bIsParty)
		{
			FPlayerInfo* PartyPlayerInfo = FindPlayerInfoWithGuid(Party.TargetGUID);
			PartyPlayerInfo->PlayerController->Client_StartRaid(HostIP);
		}
	}
}

void AEosVillageGameMode::CanStartRaid(const FGuid& HostGUID)
{
	FPlayerInfo* HostPlayerInfo = FindPlayerInfoWithGuid(HostGUID);
	
	if (!HostPlayerInfo->bIsParty)
	{
		HostPlayerInfo->PlayerController->Client_AddSelf(*HostPlayerInfo);
		HostPlayerInfo->PlayerController->Client_SetRaid();
	}
}