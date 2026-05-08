// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, FName, StatName, float, NewValue);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable, BlueprintType )
class ZOMBIEFPS_API UStatManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName,float> StatsMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FName,float> BaseStatsMap;

	UPROPERTY(BlueprintAssignable)
	FOnStatChanged OnStatChanged;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetStat(FName StatName, float &OutStat);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetBaseStat(FName StatName, float &OutStat);

	UFUNCTION(BlueprintCallable)
	bool AddStat(FName StatName, float BaseValue);
	
	
	UFUNCTION(BlueprintCallable)
	void IncreaseStatFlat(FName StatName,float IncreaseAmount, bool UseBaseStat, float &OutStat);

	UFUNCTION(BlueprintCallable)
	void IncreaseStatMult(FName StatName,float Multiplier,bool UseBaseStat, float &OutStat);

	UFUNCTION(BlueprintCallable)
	void IncreaseStatPercentage(FName StatName,float Percentage,bool UseBaseStat, float &OutStat);

	UFUNCTION(BlueprintCallable)
	void IncreaseStatFlatForDuration(FName StatName,float IncreaseAmount, bool UseBaseStat, float Duration, float &OutStat);
	
	UFUNCTION(BlueprintCallable)
	void IncreaseStatMultForDuration(FName StatName,float Multiplier, bool UseBaseStat, float Duration, float &OutStat);

	UFUNCTION(BlueprintCallable)
	void IncreaseStatPercentageForDuration(FName StatName,float Percentage, bool UseBaseStat, float Duration, float &OutStat);

	UFUNCTION(BlueprintCallable)
	void ResetStatToPreviousValue(FName StatName, float PreviousValue);
	
	
};
