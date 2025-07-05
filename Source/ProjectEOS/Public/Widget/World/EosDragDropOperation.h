// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "EosDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEOS_API UEosDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	class UEosInventoryComponent* InventoryComponent;
	int32 Index;
	
protected:

private:

};
