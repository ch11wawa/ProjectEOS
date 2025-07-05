// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystem/PlayerState/EosBasePlayerState.h"
#include "AbilitySystem/EosAbilitySystemComponent.h"
#include "AbilitySystem/EosAttributeSet.h"
#include "Components/Inventory/EosInventoryComponent.h"

AEosBasePlayerState::AEosBasePlayerState()
{
	NetUpdateFrequency = 300.f;

	EosAbilitySystemComponent = CreateDefaultSubobject<UEosAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	EosAbilitySystemComponent->SetIsReplicated(true);
	EosAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	PlayerInventoryComponent = CreateDefaultSubobject<UEosInventoryComponent>(TEXT("PlayerInventoryComponent"));

	EosAttributeSet = CreateDefaultSubobject<UEosAttributeSet>(TEXT("AbilityAttributeSet"));

}
