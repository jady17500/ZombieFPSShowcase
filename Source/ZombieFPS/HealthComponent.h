// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSUtils.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeathChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHeal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageTaken, AActor*, Attacker, EDamageType, DamageType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeath, AActor*, Killer, EDamageType, DamageType);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class ZOMBIEFPS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

			
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int MaxHealth;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int CurrentHealth;
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsDead = false;
	
	UPROPERTY(BlueprintAssignable)
	FOnHeal OnHeal;
	
	UPROPERTY(BlueprintAssignable)
	FOnDamageTaken OnDamageTaken;
	
	UPROPERTY(BlueprintAssignable)
	FOnHeathChanged OnHeathChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetHealth(int NewHealth);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual int GetHealth(){return CurrentHealth;}
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual int GetMaxHealth(){return MaxHealth;}
	
	UFUNCTION(BlueprintCallable)
	virtual void Heal(int HealAmount);
	
	UFUNCTION(BlueprintCallable)
	virtual void Damage(int Damage, AActor* Attacker, EDamageType DamageType);
	
	UFUNCTION(BlueprintCallable)
	virtual void Death(AActor* Killer, EDamageType DamageType);
};
