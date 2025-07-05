// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EosBaseCharacter.h"
#include "ProjectEOS/Public/Interfaces/EosInteractableInterface.h"
#include "EosBaseNonePlayerCharacter.generated.h"

class AEosBasePlayerController;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API AEosBaseNonePlayerCharacter : public AEosBaseCharacter, public IEosInteractableInterface
{
	GENERATED_BODY()
	
public:
	AEosBaseNonePlayerCharacter();

	//�������� �̸��� ������ ���� �������Ʈ���� �����ͼ� ���������̺��� �̸��� �־��ش�
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText Name;

protected:
	virtual void BeginPlay()override;

private:	

public:
	//��ȣ�ۿ� �Լ�
	virtual void InteractWith(AActor* InterActor);

/// CUSUTOM FUNCTION
	//�������� �̸��� ������ �Լ�
	UFUNCTION(BlueprintCallable)
	virtual FText LookAt();

	UFUNCTION(BlueprintPure)
	AEosBasePlayerController* GetEosPlayerController(AActor* Actor) const;


/// CUSUTOM VARIABLE
private:
	AEosBasePlayerController* EosPlayerController;

	UPROPERTY(EditAnywhere)
	FName NpcID;

	UPROPERTY(EditAnywhere)
	FName DialogID;

public:

///  GETTER FUNCTION
public:
	FName GetDialogID() const;
};
