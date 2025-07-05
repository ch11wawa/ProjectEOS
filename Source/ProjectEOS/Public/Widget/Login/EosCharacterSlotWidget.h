// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosCharacterSlotWidget.generated.h"

//UENUM(BlueprintType)
//enum class ECharacterClass : uint8
//{
//	GreatSword     UMETA(DisplayName = "GreatSword"),
//	Supporter        UMETA(DisplayName = "Supporter"),
//	Lancer      UMETA(DisplayName = "Lancer"),
//	Magician       UMETA(DisplayName = "Magician"),
//	None
//};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, const int32, SlotID);

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosCharacterSlotWidget : public UEosBaseWidget
{
	GENERATED_BODY()
	
/// ENGINE FUNCTION
protected:
	virtual bool Initialize() override;

	/// CUSTOM FUNCTION
public:
	UFUNCTION(BlueprintCallable)
	void OnClickedCharacter();				// Button(Charcater) On_Click Event

	UFUNCTION(BlueprintCallable)
	void ChangeImage(int Index, UTexture2D* NewImage);

	void SetTextBlockNickname(const FString NewNickname);

	void CancleSelect();

	void ShowNickname();

	/// CUSTOM VARIABLE
public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterSelected OnCharacterSelected;

protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsPress;

	UPROPERTY(EditAnywhere)
	EPlayerClassType CharacterClass;

	UPROPERTY(BlueprintReadWrite)
	FString Nickname;

	UPROPERTY(BlueprintReadWrite)
	FGuid CID;

private:
	// Bind Button
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Character;

	// Bind Image
	UPROPERTY(meta = (BindWidget))
	class UImage* Image_CharacterImage;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* SizeBox_Select;

	UPROPERTY(meta=(BindWidget))
	class USizeBox* SizeBox_Nickname;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextBlock_Nickname;

	int32 SlotID;


/// GETTER FUNCTION
public:
	UFUNCTION(BlueprintCallable)
	EPlayerClassType GetCharacterClass() const { return CharacterClass; }

	UFUNCTION()
	void SetCharacterClass(const EPlayerClassType NewCharacterClass) { CharacterClass = NewCharacterClass; GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "SetCharacterClass");
	}

	FString GetNickname() const { return Nickname; }

	UFUNCTION(BlueprintCallable)
	void SetNickname(const FString NewNickname) { Nickname = NewNickname; }

	FGuid GetCID() const { return CID; }
	void SetCID(const FGuid NewCID) { CID = NewCID; }

	int32 GetSlotID() const { return SlotID; }
	void SetSlotID(const int32 NewID) { SlotID = NewID; }
};
