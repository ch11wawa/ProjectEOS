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
//���̽� ĳ���� Ŭ���� ���� ����
//class AEosBasePlayerCharacter;

class PROJECTEOS_API IEosInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//���� �����Լ� ��ȣ�ۿ�
	//virtual void Interact(AEosBasePlayerCharacter* Character) = 0;

	//���� �����Լ� �����ۻ��
	//virtual void Use(AEosBasePlayerCharacter* Character, bool bInShop = false) {}

	//virtual void AddItem(class AEosBaseItem* ItemToAdd, AEosBasePlayerCharacter* Character) {}

	//��ȣ�ۿ� �Լ�
	virtual void InteractWith(AActor* InterActor) = 0;

	//������ �̸� �����ִ� �Լ�
	virtual FText LookAt() = 0;
};
