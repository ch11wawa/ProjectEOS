// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystem/GameMode/EosRaidGameMode.h"
#include "EosGameInstance.h"
#include "PlayerController/EosWorldPlayerController.h"


void AEosRaidGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AEosRaidGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	
	UEosGameInstance* GameInstance = Cast<UEosGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		PartyArr = GameInstance->GetPartyList();
	}

	CurrentPlayer->bIsRaid = true;
	
	if (GetNumPlayers() == PartyArr.Num())
	{
		GetWorld()->GetTimerManager().SetTimer(PlayerSpawnTimer, this, &AEosRaidGameMode::Multicast_SpawnAndPossess, 0.2f, false);
		if (PartyArr.Num() > 1)
			GetWorld()->GetTimerManager().SetTimer(PartyUITimer, this, &AEosRaidGameMode::SetParty, 3.0f, false);
	}
}

void AEosRaidGameMode::SetParty()
{
	GetWorld()->GetTimerManager().ClearTimer(PartyUITimer);

	if (PartyArr.Num() == GetNumPlayers())
	{ 
		for (auto& Current : PlayerInfoArr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Current.PlayerController->GetGuid().ToString());

			Current.PlayerController->Client_SetPartyUI(PartyArr);
		}
	}
}

void AEosRaidGameMode::UpdateParty(const FGuid TargetGUID, float NewHP)
{
	for (auto& Party : PlayerInfoArr)
	{
		if (Party.PlayerGUID != TargetGUID)
		{
			UE_LOG(LogTemp, Warning, TEXT("UpdateParty"));

			if (Party.PlayerController)
			{
				Party.PlayerController->Client_UpdatePartyUI(TargetGUID, NewHP);
			}
		}
	}
}

void AEosRaidGameMode::Multicast_SpawnAndPossess_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(PlayerSpawnTimer);

	UE_LOG(LogTemp, Warning, TEXT("SpawnAndPossess"));

	for (auto& PlayerController : PlayerControllerArr)
	{
		PlayerController->Client_GetGameInstance();
	}
}
