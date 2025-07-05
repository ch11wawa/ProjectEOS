// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Struct/EosPlayerInfo.h"
#include "EosBaseGameMode.generated.h"

class AEosBasePlayerCharacter;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API AEosBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

/// ENGINE FUNCTION
public:
	virtual void BeginPlay() override;
	virtual void OnPostLogin(AController* NewPlayer);

/// CUSTOM FUNCTION
	UFUNCTION()
	void UpdateMessage(const FText& msg);

	UFUNCTION(BlueprintCallable)
	void GetPlayerInfo(AEosWorldPlayerController* PlayerController, FPlayerInfo PlayerInfo);

	UFUNCTION(BlueprintCallable)
	virtual void SpawnPlayerCharacter(class AEosWorldPlayerController* PlayerController);

protected:
	FORCEINLINE FPlayerInfo* FindPlayerInfoWithGuid(const FGuid GUID)
	{
		for (auto& PlayerInfo : PlayerInfoArr)
		{
			if (PlayerInfo.PlayerGUID == GUID)
			{
				return&PlayerInfo;
			}
		}
		return nullptr;
	}

	FORCEINLINE FPlayerInfo* FindPlayerInfoWithController(const class AEosWorldPlayerController* PlayerController)
	{
		for (auto& PlayerInfo : PlayerInfoArr)
		{
			if (PlayerInfo.PlayerController == PlayerController)
			{
				return&PlayerInfo;
			}
		}
		return nullptr;
	}

/// CUSTOM VARIABLE
	UPROPERTY()
	TArray<AActor*> PlayerStarts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TArray<class AEosWorldPlayerController*> PlayerControllerArr;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	class AEosWorldPlayerController* CurrentPlayer;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<AEosBasePlayerCharacter> GreatSwordClass;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<AEosBasePlayerCharacter> HealerClass;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<AEosBasePlayerCharacter> LancerClass;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<AEosBasePlayerCharacter> MagicianClass;

	UPROPERTY(BlueprintReadWrite, Category = "Player")
	TArray<FPlayerInfo> PlayerInfoArr;

	UPROPERTY()
	int StartPoint = 0;

/// GETTER FUNCTION
/// HELPER FUNCTION
};
