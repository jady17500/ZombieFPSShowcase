// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "PlayerHealth.generated.h"

/**
 * 
 */
class UStatManagerComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevive);
UCLASS()
class ZOMBIEFPS_API UPlayerHealth : public UHealthComponent
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int RegenerationRate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RegenerationDelay;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RegenerationTick;
	
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle RegenerationRateTimer;
	
	UPROPERTY(BlueprintReadOnly)
	FTimerHandle RegenerationDelayTimer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseStatManager;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanRegenerate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition="bUseStatManager",EditConditionHides))
	FName HealthKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition="bUseStatManager",EditConditionHides))
	FName RegenerationDelayKey;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition="bUseStatManager",EditConditionHides))
	FName RegenerationRateKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition="bUseStatManager",EditConditionHides))
	FName RegenerationTickKey;
	
	UPROPERTY(BlueprintReadOnly, meta = (EditCondition="bUseStatManager",EditConditionHides))
	TWeakObjectPtr<UStatManagerComponent> StatManager;
	
	UPROPERTY(BlueprintReadWrite)
	float RequiredReviveCharges = 100;
	
	UPROPERTY(BlueprintReadWrite)
	float CurrentReviveCharges = 0;
	
	UPROPERTY(BlueprintReadWrite)
	float BleedOutTime = 60;
	
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle BleedOutTimer;
	
	UPROPERTY(BlueprintAssignable)
	FOnRevive OnRevive;
	
	UFUNCTION(BlueprintCallable)
	void Regenerate();
	
	UFUNCTION(BlueprintCallable)
	void BleedOut();
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_AddReviveCharges(float ReviveCharges);
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Multicast_Revive();
	
	virtual void Multicast_Death(AActor* Killer, EDamageType DamageType) override;
	
	UFUNCTION(BlueprintCallable)
	void StartRegenerate();
	
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(FName StatKey, float OutStat);

	UFUNCTION(BlueprintCallable)
	void UpdateRegeneration(FName StatKey, float OutStat);
	
	UFUNCTION(BlueprintCallable)
	void CancelRegeneration(AActor* Attacker, EDamageType DamageType);

	UFUNCTION(BlueprintCallable)
	void InitStats();
	
	UFUNCTION(BlueprintCallable)
	void InitBlastResistance();
	
	UFUNCTION(BlueprintCallable)
	void ReduceBlastDamage(AActor* Attacker, EDamageType DamageType, int& Damage);
};
