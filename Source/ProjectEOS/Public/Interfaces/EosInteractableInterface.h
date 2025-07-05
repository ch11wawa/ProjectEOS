// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EosInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEosInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
//베이스 캐릭터 클래스 전방 선언
//class AEosBasePlayerCharacter;

class PROJECTEOS_API IEosInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//순수 가상함수 상호작용
	//virtual void Interact(AEosBasePlayerCharacter* Character) = 0;

	//순수 가상함수 아이템사용
	//virtual void Use(AEosBasePlayerCharacter* Character, bool bInShop = false) {}

	//virtual void AddItem(class AEosBaseItem* ItemToAdd, AEosBasePlayerCharacter* Character) {}

	//상호작용 함수
	virtual void InteractWith(AActor* InterActor) = 0;

	//아이템 이름 보여주는 함수
	virtual FText LookAt() = 0;
};
