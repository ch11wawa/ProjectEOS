// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/EosBaseWidget.h"
#include "EosInventoryMainWidget.generated.h"

class UEosSlotContainerWidget;
class UTextureRenderTarget2D;
class AEosInventoryPreview;
class UImage;

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosInventoryMainWidget : public UEosBaseWidget
{
	GENERATED_BODY()

	///ENGINE FUNCTION

private:
	virtual void NativeConstruct() override;

public:
	//void OpenInventory();
	//void CloseInventory();
	
protected:
	UPROPERTY(meta = (BindWidget))
	UEosSlotContainerWidget* WBP_SlotContainer_1;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Showcase")
	//UTextureRenderTarget2D* PreviewRenderTarget;

	UPROPERTY(EditDefaultsOnly, Category = "Showcase")
	TSubclassOf<AActor> ShowcaseClass;

	UPROPERTY()
	AEosInventoryPreview* ShowcaseStage;

	//UPROPERTY(meta = (BindWidget))
	//UImage* CharacterPreviewImage;
};
