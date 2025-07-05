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

	// 기본 생성자
	FPlayerInfo()
		: PlayerGUID(FGuid())                 // FGuid는 기본 생성자를 호출하여 초기화
		, PlayerController(nullptr)           // 컨트롤러는 nullptr로 초기화
		, NickName(TEXT("Default NickName"))  // 닉네임은 "Default NickName"으로 초기화
		, CharacterClass(EPlayerClassType::Empty)                   // 캐릭터 클래스는 Empty으로 초기화
		, bIsParty(false)
		, bIsHost(false)
	{}
};

