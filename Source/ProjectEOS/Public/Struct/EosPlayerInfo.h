#pragma once

#include "Character/PlayerCharacter/EosBasePlayerCharacter.h"
#include "EosPlayerInfo.generated.h"

class AEosWorldPlayerController;

USTRUCT(BlueprintType)
struct FPartyInviteInfo
{
public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGuid TargetGUID;

	UPROPERTY(BlueprintReadWrite)
	bool bIsParty = false;

	FPartyInviteInfo() :TargetGUID(FGuid()), bIsParty(false) {}
	FPartyInviteInfo(FGuid& NewTargetGUID, bool bNewIsParty) : TargetGUID(NewTargetGUID), bIsParty(bNewIsParty) {}

};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGuid PlayerGUID;

	UPROPERTY(BlueprintReadWrite)
	AEosWorldPlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite)
	FString NickName;

	UPROPERTY(BlueprintReadWrite)
	EPlayerClassType CharacterClass;

	UPROPERTY(BlueprintReadOnly)
	bool bIsParty;

	UPROPERTY(BlueprintReadOnly)
	bool bIsHost;

	UPROPERTY(BlueprintReadWrite)
	TArray<FPartyInviteInfo> PartyInviteList;

	// �⺻ ������
	FPlayerInfo()
		: PlayerGUID(FGuid())                 // FGuid�� �⺻ �����ڸ� ȣ���Ͽ� �ʱ�ȭ
		, PlayerController(nullptr)           // ��Ʈ�ѷ��� nullptr�� �ʱ�ȭ
		, NickName(TEXT("Default NickName"))  // �г����� "Default NickName"���� �ʱ�ȭ
		, CharacterClass(EPlayerClassType::Empty)                   // ĳ���� Ŭ������ Empty���� �ʱ�ȭ
		, bIsParty(false)
		, bIsHost(false)
	{}
};

