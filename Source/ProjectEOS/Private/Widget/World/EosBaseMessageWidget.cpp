// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosBaseMessageWidget.h"
#include "Components/TextBlock.h"

void UEosBaseMessageWidget::SetMessage(const FText NewMessage)
{
	TextBlock_Message->SetText(NewMessage);
}
