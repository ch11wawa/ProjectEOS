// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosBaseSelectionPageWidget.generated.h"

class UEosCharacterSlotWidget;
class UEosGameInstance;
/**
 *
 */
UCLASS()
class PROJECTEOS_API UEosBaseSelectionPageWidget : public UEosBaseWidget
{
	GENERATED_BODY()

/// ENGINE FUNCTION
protected:
	virtual void NativeConstruct() override;

/// CUSTOM FUNCTION
public:
	// �������� �߰��� ���� ����
	UFUNCTION(BlueprintCallable)
	virtual void SelectCharacter(const int32 SlotID);


protected:
	// �������� ���� �߰�
	UFUNCTION(BlueprintCallable)
	virtual void AddCharacterSlots();

	UFUNCTION(BlueprintImplementableEvent)
	void GetCharacterInfoFromDatabase();

	UFUNCTION(BlueprintPure)
	FString EnumToString(EPlayerClassType ClassType);

protected:
	UFUNCTION()
	virtual void OnClickedSelect();

	UFUNCTION(BlueprintCallable)
	void SaveCharacterData();

/// CUSTOM VARIABLE
protected:
	// ĳ���� �̹��� ���� �迭
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UTexture2D*> CharacterImages;

	UPROPERTY(EditAnywhere, Category = "SelectCharacter")
	TSubclassOf<UEosCharacterSlotWidget> CharacterSlotClass;

	UPROPERTY()
	UEosCharacterSlotWidget* CharacterSlotInstance;

	UPROPERTY()
	TArray<UEosCharacterSlotWidget*> CharacterSlots;

	UPROPERTY(BlueprintReadOnly)
	UEosCharacterSlotWidget* SelectedSlot;

	UPROPERTY(BlueprintReadOnly)
	FGuid GUID;

	UPROPERTY(BlueprintReadWrite)
	FGuid CID;

	UPROPERTY(BlueprintReadWrite)
	FString Nickname;

	UPROPERTY(BlueprintReadOnly)
	UEosGameInstance* EosGameInstance;

	UPROPERTY(BlueprintReadWrite)
	float CharacterNum;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Select;

private:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_SlotBox;


};
