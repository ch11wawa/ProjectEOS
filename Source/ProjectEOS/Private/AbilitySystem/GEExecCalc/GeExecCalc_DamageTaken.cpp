// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GeExecCalc_DamageTaken.h"
#include "AbilitySystem/EosAttributeSet.h"
#include "EosGameplayTags.h"

// ��꿡 ����� �Ӽ� ĸ�� ����
struct FEosDamageCapture
{
	// ����
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FEosDamageCapture()
	{
		//���� Class, Capture, Target, Snapshot �� ��Ÿ ������ ���
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEosAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEosAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEosAttributeSet, DamageTaken, Target, false)
	}
};

// ĸó�� ���� ȣ�� �� �� ���� ����
// ��ܿ� DEFINE_ATTRIBUTE_CAPTUREDEF ��ũ�η� ���ǵ� ������ ��Ÿ �����͸� ��Ȱ��
static const FEosDamageCapture& GetEosDamageCapture()
{
	static FEosDamageCapture EosDamageCapture;
	return EosDamageCapture;
}

// 
UGeExecCalc_DamageTaken::UGeExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetEosDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetEosDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetEosDamageCapture().DamageTakenDef);
}

// ����Ʈ ���� ��
void UGeExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEosDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetEosDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	// ����� ������ ����
	float BaseDamage = 0.f;
	float SkillDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedSmashAttackComboCount = 0;
	
	// SetByCaller�� ���� ���� ���� �и�
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		// Ű�� ������ ���� ������ �� ����
		if (TagMagnitude.Key.MatchesTagExact(EosGameplayTags::Common_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(EosGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(EosGameplayTags::Player_SetByCaller_AttackType_Smash))
		{
			UsedSmashAttackComboCount = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(EosGameplayTags::Player_SetByCaller_AttackType_Skill))
		{
			SkillDamage = TagMagnitude.Value;
		}
	}

	// ���� ���ǿ� ���� ����
	if (UsedLightAttackComboCount != 0)
	{
		//��Ÿ 2Ÿ���� ����� 5% ����
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;

		BaseDamage *= DamageIncreasePercentLight;
	}
	//���Ž� ī��Ʈ�� ����� 15% ���� (0Ÿ ���Ž� ������ ��� 8% ����)
	/*if (UsedSmashAttackComboCount == 0)
	{
		const float DamageIncreasePercentSmash = 1 * 0.8f + 1.f;

		BaseDamage *= DamageIncreasePercentSmash;
	}*/
	if (UsedSmashAttackComboCount != 0)
	{
		const float DamageIncreasePercentSmash = UsedSmashAttackComboCount * 0.15f + 1.f;

		BaseDamage *= DamageIncreasePercentSmash;
	}

	//���� ����RE
	const float FinalDamage = BaseDamage * SourceAttackPower / TargetDefensePower;

	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier
		(
			FGameplayModifierEvaluatedData
			(
				GetEosDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}
}