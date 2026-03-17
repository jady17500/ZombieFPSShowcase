// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "PlayerHealth.generated.h"

/**
 * 
 */
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
	
	UFUNCTION(BlueprintCallable)
	void Regenerate();
	
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
};
