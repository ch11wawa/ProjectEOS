// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "EosBasePlayerState.generated.h"

class UEosAbilitySystemComponent;
class UEosAttributeSet;
class UEosInventoryComponent;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API AEosBasePlayerState : public APlayerState
{
	GENERATED_BODY()
	
	AEosBasePlayerState();

	public :

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UEosAbilitySystemComponent* EosAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	UEosAttributeSet* EosAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UEosInventoryComponent* PlayerInventoryComponent;
}; 
