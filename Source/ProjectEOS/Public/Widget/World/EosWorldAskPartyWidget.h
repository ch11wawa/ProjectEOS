// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosWorldAskPartyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosWorldAskPartyWidget : public UEosBaseWidget
{
	GENERATED_BODY()

/// ENGINE FUNCTION
public:
	UEosWorldAskPartyWidget();

/// CUSTOM FUNCTION
public:
	UFUNCTION(BlueprintCallable)
	void AnswerParty(const FGuid HostGUID, const FString& HostNickName);

protected:
	UFUNCTION(BlueprintCallable)
	void OnClick_Accept();

	UFUNCTION(BlueprintCallable)
	void OnClick_Decline();


/// CUSTOM VARIABLE
protected:
	UPROPERTY(BlueprintReadWrite)
	FGuid HostGuid;

	UPROPERTY(BlueprintReadOnly)
	class AEosWorldPlayerController* Owner;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_HostNickName;

/// GETTER FUNCTION
/// HELPER FUNCTION
};
