// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosWorldPartyWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UEosWorldPartyWidget::UpdatePartyHP(float NewHP)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("%.1f%%"), NewHP * 100));

	SoulAlpha = NewHP;

	FWidgetTransform NewTransform = Image_Soul->RenderTransform;
	NewTransform.Scale = FVector2D(NewHP, NewHP);
	Image_Soul->SetRenderTransform(NewTransform);

	TextBlock_HPPercent->SetText(FText::FromString(FString::Printf(TEXT("%.1f%%"), NewHP * 100)));
	
	InvalidateLayoutAndVolatility();
}

void UEosWorldPartyWidget::SetPartyGuid(const FGuid TargetGuid)
{
	PlayerGuid = TargetGuid;
}

FGuid UEosWorldPartyWidget::GetPartyGuid() const
{
	return PlayerGuid;
}

void UEosWorldPartyWidget::SetPartyUI(const FText& NewNickName, UTexture2D* NewImage)
{
	if (Image_Face && TextBlock_NickName)
	{
		Image_Face->SetBrushFromTexture(NewImage);
		TextBlock_NickName->SetText(NewNickName);
	}
}