// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/EosStructTypes.h"
#include "AbilitySystem/Abilities/EosGameplayAbility.h"


bool FPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && GrantAbility;
}