// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"

#include "EosBaseProjectile.generated.h"

class UBoxComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;
struct FGameplayEventData;

UENUM(BlueprintType)
enum class EProjectileEffectType : uint8
{
	Particle,
	Niagara
};

UENUM(BlueprintType)
enum class EProjectileReactPolicy : uint8
{
	OnHit,
	OnBeginOverlap
};

UENUM(BlueprintType)
enum class EProjectileReactTypePolicy : uint8
{
	LightReact,
	HeavyReact
};


UCLASS()
class PROJECTEOS_API AEosBaseProjectile : public AActor
{
	GENERATED_BODY()
	
///ENGINE FUNCTION

public:	
	// Sets default values for this actor's properties
	AEosBaseProjectile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

///CUSTOM FUNCTION

	void SetOwnerIgnoreCollision(AActor* InOwner);

///CUSTOM VARIABLE
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UBoxComponent* ProjectileCollisionBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UParticleSystemComponent* ProjectileParticleComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* ProjectileNiagaraComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	EProjectileReactPolicy ProjectileReactPolicy = EProjectileReactPolicy::OnHit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	EProjectileReactTypePolicy ProjectileReactTypePolicy = EProjectileReactTypePolicy::LightReact;

	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle ProjectileDamageEffectSpecHandle;

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "EOS | Projectile")
	void SetDamageEffectSpecHandle(const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Spawn Projectile Hit FX"))
	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);

private:
	void HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload);

protected:
	FGameplayEffectSpecHandle ProjectileDamegeEffectSpecHandle;
};
