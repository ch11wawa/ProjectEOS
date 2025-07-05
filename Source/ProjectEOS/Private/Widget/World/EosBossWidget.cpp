// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/World/EosBossWidget.h"
#include "Character/EnemyCharacter/EosBaseEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/UI/EosBaseUIComponent.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "AbilitySystem/EosAttributeSet.h"

void UEosBossWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	AEosBaseEnemyCharacter* Enemy = Cast<AEosBaseEnemyCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AEosBaseEnemyCharacter::StaticClass()));

	if (Enemy && Enemy->ActorHasTag(FName("Boss")))
	{
		TextBlock_BossName->SetText(FText::FromName(Enemy->Tags[1]));
		TextBlock_BossNameEn->SetText(FText::FromName(Enemy->Tags[2]));

		DynamicMaterial = UMaterialInstanceDynamic::Create(ProgressBarMaterial, this);
		ProgressBar_Boss->SetBrushFromMaterial(DynamicMaterial);


		float CurrentHealth = Enemy->GetEosAttributeSet()->GetCurrentHealth();
		float MaxHealth = Enemy->GetEosAttributeSet()->GetMaxHealth();

		UpdateHP(CurrentHealth, MaxHealth);

		EnemyUIComponent = BringUIComponent(Enemy);

		if (EnemyUIComponent)
		{
			EnemyUIComponent->OnHealthChanged.AddDynamic(this, &UEosBossWidget::UpdateHP);
		}
	}

}

void UEosBossWidget::NativeDestruct()
{
	if (EnemyUIComponent)
	{
		EnemyUIComponent->OnHealthChanged.RemoveDynamic(this, &UEosBossWidget::UpdateHP);
	}
	
	Super::NativeDestruct();
}

void UEosBossWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CurrentAlpha += (InDeltaTime / ResponseTime);

	float value = FMath::InterpEaseOut(PreviousPercent, Percent, FMath::Clamp(CurrentAlpha, 0.0f, 1.0f), 2.0f);

	DynamicMaterial->SetScalarParameterValue("percentage", value);
}

void UEosBossWidget::UpdateHP(float CurrentHealth, float MaxHealth)
{
	float NewPercent = (FMath::Fmod(CurrentHealth, MaxHealth/TotalLines)) / (MaxHealth / TotalLines);
	if (CurrentHealth == MaxHealth) NewPercent = CurrentHealth/MaxHealth;
	
	float CurrentLines = FMath::CeilToFloat(CurrentHealth / (MaxHealth / TotalLines));
	//FLinearColor NewBackColor, NewColor;

	//switch ((int)CurrentLines)
	//{
	//case 1:
	//	NewColor = FLinearColor::FLinearColor(0.173035f, 0.0f, 1.0f, 1.0f);		// 보라색
	//	NewBackColor = FLinearColor::FLinearColor(0.173035f, 0.0f, 1.0f, 1.0f);		// 보라색
	//	break;

	//case 2:
	//	NewBackColor = FLinearColor::FLinearColor(0.000906f, 0.0f, 1.0f, 1.0f);		// 파란색
	//	break;

	//case 3:
	//	NewColor = FLinearColor::FLinearColor(0.000906f, 0.0f, 1.0f, 1.0f);		// 파란색
	//	NewBackColor = FLinearColor::FLinearColor(0.000906f, 0.0f, 1.0f, 1.0f);		// 파란색
	//	break;

	//case 4:
	//	NewBackColor = FLinearColor::FLinearColor(0.331811f, 0.062021f, 0.0f, 1.0f);		// 주황색
	//	break;

	//case 5:
	//	NewColor = FLinearColor::FLinearColor(0.331811f, 0.062021f, 0.0f, 1.0f);		// 주황색
	//	NewBackColor = FLinearColor::FLinearColor(0.331811f, 0.062021f, 0.0f, 1.0f);		// 주황색
	//	break;

	//case 6:
	//	NewBackColor = FLinearColor::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);		// 빨간색
	//	break;

	//case 7:
	//	NewColor = FLinearColor::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);		// 빨간색
	//	NewBackColor = FLinearColor::FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);		// 빨간색
	//	break;

	//case 8:
	//	NewBackColor = FLinearColor::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);		// 흰색
	//	break;

	//case 9:
	//	NewColor = FLinearColor::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);		// 흰색
	//	NewBackColor = FLinearColor::FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);		// 흰색
	//	break;

	//case 10:
	//	NewBackColor = FLinearColor::FLinearColor(0.173035f, 0.0f, 1.0f, 1.0f);		// 보라색
	//	break;

	//}

	//float Value = FMath::Clamp((255 / (TotalLines - 1)) * (TotalLines - CurrentLines), 255, 0);
	//FLinearColor NewColor = FLinearColor::MakeFromHSV8(160, Value, 150);
	//FLinearColor NewBackColor = FLinearColor::MakeFromHSV8(160, Value + (255 / (TotalLines - 1)), 150);

	////ProgressBar_BossHP->SetFillColorAndOpacity(NewColor);
	//SetBackgroundColor(NewBackColor);
	//	
	////ProgressBar_BossHP->SetPercent(NewPercent);

	//float test = FMath::Fmod(CurrentHealth, TotalLines);

	//FLinearColor NewColor;
	//FLinearColor NewBackColor;

	//switch ((int)CurrentLines)
	//{
	//case 10:
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), (int)CurrentLines));
	//	NewColor = FLinearColor::FLinearColor(0.485f, 0.485f, 0.0f);
	//	NewBackColor = FLinearColor::FLinearColor(0.485f, 0.0f, 0.0f);
	//	break;

	//case 9:
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), (int)CurrentLines));
	//	NewColor = FLinearColor::FLinearColor(0.485f, 0.0f, 0.0f);
	//	NewBackColor = FLinearColor::FLinearColor(0.0f, 0.485f, 0.485f);
	//	break;

	//}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%d"), (int)CurrentLines));


	float Value = FMath::Clamp((0.318547f / (TotalLines - 1)) * (TotalLines - CurrentLines), 0.0f, 0.318547f);
	float BackValue = FMath::Clamp(Value + 0.0318547f, 0.0f, 0.318547f); ;
	FLinearColor NewColor = FLinearColor::FLinearColor(Value, Value+0.056196f, 0.318547f);
	FLinearColor NewBackColor = FLinearColor::FLinearColor(BackValue, BackValue + 0.056196f, 0.318547f, 0.1f);
	//FLinearColor NewBackColor = FLinearColor::FLinearColor(0.0f, 0.485f, 0.485f, 0.3f);

	DynamicMaterial->SetVectorParameterValue("Color", NewColor);
	DynamicMaterial->SetVectorParameterValue("Background", NewBackColor);

	PreviousPercent = Percent;
	Percent = FMath::Clamp(NewPercent, 0.0f, 1.0f);
	CurrentAlpha = 0.0f;

}

void UEosBossWidget::SetBackgroundColor(FLinearColor NewColor)
{/*
	if (ProgressBar_BossHP)
	{
		FProgressBarStyle NewStyle = ProgressBar_BossHP->WidgetStyle;
		NewStyle.BackgroundImage.TintColor = FSlateColor(NewColor);
		ProgressBar_BossHP->SetWidgetStyle(NewStyle);
	}*/
}
