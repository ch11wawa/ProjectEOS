// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystem/GameMode/EosBaseGameMode.h"
#include "PlayerController/EosWorldPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "CoreSystem/PlayerState/EosBasePlayerState.h"


void AEosBaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
}

void AEosBaseGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	CurrentPlayer = Cast<AEosWorldPlayerController>(NewPlayer);
	if (CurrentPlayer)
	{
		PlayerControllerArr.Add(CurrentPlayer);

		FPlayerInfo NewPlayerInfo;
		NewPlayerInfo.PlayerController = CurrentPlayer;
		PlayerInfoArr.Add(NewPlayerInfo);
	}
}

void AEosBaseGameMode::UpdateMessage(const FText& msg)
{
	for (auto& Player : PlayerControllerArr)
	{
		if (Player)
		{
			Player->Client_SendMessage(msg);
		}
	}
}

void AEosBaseGameMode::GetPlayerInfo(AEosWorldPlayerController* PlayerController, FPlayerInfo PlayerInfo)
{
	FPlayerInfo* CurrentPlayerInfo = FindPlayerInfoWithController(PlayerController);
	CurrentPlayerInfo->NickName = PlayerInfo.NickName;
	CurrentPlayerInfo->CharacterClass = PlayerInfo.CharacterClass;
	CurrentPlayerInfo->PlayerGUID = PlayerInfo.PlayerGUID;
	PlayerController->SetGuid(CurrentPlayerInfo->PlayerGUID);
	UE_LOG(LogTemp, Warning, TEXT("GetPlayerInfo : %s"), *CurrentPlayerInfo->PlayerGUID.ToString());

	SpawnPlayerCharacter(PlayerController);
}

void AEosBaseGameMode::SpawnPlayerCharacter(AEosWorldPlayerController* PlayerController)
{
	TSubclassOf<AEosBasePlayerCharacter> LoadedCharacterClass = nullptr;

	FPlayerInfo* CurrentPlayerInfo = FindPlayerInfoWithGuid(PlayerController->GetGuid());
	UE_LOG(LogTemp, Warning, TEXT("SpawnPlayerCharacter : %s"), *CurrentPlayerInfo->PlayerGUID.ToString());
	EPlayerSkillType PlayerSkillType = EPlayerSkillType::None;

	switch (CurrentPlayerInfo->CharacterClass)
	{
	case EPlayerClassType::GreatSword:
		LoadedCharacterClass = GreatSwordClass;
		PlayerSkillType = EPlayerSkillType::Stamina;
		break;
	case EPlayerClassType::Healer:
		LoadedCharacterClass = HealerClass;
		PlayerSkillType = EPlayerSkillType::Mana;
		break;
	case EPlayerClassType::Lancer:
		LoadedCharacterClass = LancerClass;
		PlayerSkillType = EPlayerSkillType::Stamina;
		break;
	case EPlayerClassType::Mage:
		LoadedCharacterClass = MagicianClass;
		PlayerSkillType = EPlayerSkillType::Stamina;
		break;
	}

	if (LoadedCharacterClass && PlayerStarts[StartPoint])
	{
		FTransform SpawnTransform = PlayerStarts[StartPoint]->GetActorTransform();

		AEosBasePlayerCharacter* SpawnCharacter = GetWorld()->SpawnActor<AEosBasePlayerCharacter>
			(
				LoadedCharacterClass,
				SpawnTransform
			);
		UE_LOG(LogTemp, Warning, TEXT("Spawn"));

		if (SpawnCharacter)
		{
			PlayerController->Possess(SpawnCharacter);
			SpawnCharacter->SetPlayerSkillType(PlayerSkillType);
			if (SpawnCharacter->Controller == PlayerController)
			{
				UE_LOG(LogTemp, Warning, TEXT("Possess"));
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("No Possess"));
		}
	}

	if (StartPoint < PlayerStarts.Num()-1)
		StartPoint++;
	else
		StartPoint = 0;
}


