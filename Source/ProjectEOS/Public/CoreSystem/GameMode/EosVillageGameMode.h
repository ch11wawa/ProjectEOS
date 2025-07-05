// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreSystem/GameMode/EosBaseGameMode.h"
#include "EosVillageGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API AEosVillageGameMode : public AEosBaseGameMode
{
	GENERATED_BODY()
/// ENGINE FUNCTION
	virtual void OnPostLogin(AController* NewPlayer);

/// CUSTOM FUNCTION
public:
	UFUNCTION()
	void CreateParty(const FGuid& HostGUID, const FString& TargetNickName);

	UFUNCTION(BlueprintCallable)
	void AnswerParty(const FGuid& HostGUID, const FGuid& TargetGUID, const bool bIsParty);

	UFUNCTION()
	void StartRaid(const FGuid& HostGUID, const FString& HostIP);

	UFUNCTION()
	void CanStartRaid(const FGuid& HostGUID);
};
/// CUSTOM VARIABLE
/// GETTER FUNCTION
/// HELPER FUNCTION