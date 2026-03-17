// Fill out your copyright notice in the Description page of Project Settings.


#include "StatManagerComponent.h"

// Sets default values for this component's properties
UStatManagerComponent::UStatManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<FName> StatsNames;
	StatsMap.GetKeys(StatsNames);
	for (auto Name : StatsNames)
		BaseStatsMap.Add(Name, StatsMap[Name]);
	
}


// Called every frame
void UStatManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UStatManagerComponent::GetStat(FName StatName, float &OutStat)
{
	if (StatsMap.Contains(StatName))
	{
		OutStat = StatsMap[StatName];
		return true;
	}
	OutStat = 0;
	return false;
}

bool UStatManagerComponent::GetBaseStat(FName StatName, float &OutStat)
{
	if (BaseStatsMap.Contains(StatName))
	{
		OutStat = BaseStatsMap[StatName];
		return true;
	}
	OutStat = 0;
	return false;
}

bool UStatManagerComponent::AddStat(FName StatName, float BaseValue)
{
	if (StatsMap.Contains(StatName))
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"ADD STAT FAILED:STAT ALREADY EXISTS");
		return false;
	}
	
	StatsMap.Add(StatName, BaseValue);
	BaseStatsMap.Add(StatName, BaseValue);
	return true;
	
}

void UStatManagerComponent::IncreaseStatFlat(FName StatName, float IncreaseAmount, bool UseBaseStat, float &OutStat)
{
	if (StatsMap.Contains(StatName))
	{
		if (UseBaseStat)
			StatsMap[StatName] += BaseStatsMap[StatName] + IncreaseAmount;
		else
			StatsMap[StatName] += IncreaseAmount;
		
		OnStatChanged.Broadcast(StatName, StatsMap[StatName]);
	}

	OutStat = StatsMap[StatName];
		
}

void UStatManagerComponent::IncreaseStatMult(FName StatName, float Multiplier, bool UseBaseStat, float &OutStat)
{
	if (StatsMap.Contains(StatName))
	{
		if (UseBaseStat)
			StatsMap[StatName] += BaseStatsMap[StatName] * Multiplier;
		else
			StatsMap[StatName] *= Multiplier;
	
		OnStatChanged.Broadcast(StatName, StatsMap[StatName]);
	}

	OutStat = StatsMap[StatName];
}

void UStatManagerComponent::IncreaseStatPercentage(FName StatName, float Percentage, bool UseBaseStat, float &OutStat)
{
	if (StatsMap.Contains(StatName))
	{
		if (UseBaseStat)
			StatsMap[StatName] += BaseStatsMap[StatName] * (Percentage / 100.0f);
		else
			StatsMap[StatName] += StatsMap[StatName] * (Percentage / 100.0f);
	
		OnStatChanged.Broadcast(StatName, StatsMap[StatName]);
	}
	
	OutStat = StatsMap[StatName];
}

void UStatManagerComponent::IncreaseStatFlatForDuration(FName StatName, float IncreaseAmount, bool UseBaseStat,
	float Duration, float &OutStat)
{
	float PrevValue;
	if (StatsMap.Contains(StatName))
	{
		PrevValue = StatsMap[StatName];
		if (UseBaseStat)
			StatsMap[StatName] += BaseStatsMap[StatName] + IncreaseAmount;
		else
			StatsMap[StatName] += IncreaseAmount;
		
		OnStatChanged.Broadcast(StatName, StatsMap[StatName]);
	}

	OutStat = StatsMap[StatName];

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	TimerDelegate.BindUFunction(this, FName("ResetStatToPreviousValue"), StatName, PrevValue); 
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Duration,false);
}

void UStatManagerComponent::IncreaseStatMultForDuration(FName StatName, float Multiplier, bool UseBaseStat,
	float Duration, float &OutStat)
{
	float PrevValue;
	if (StatsMap.Contains(StatName))
	{
		PrevValue = StatsMap[StatName];
		if (UseBaseStat)
			StatsMap[StatName] += BaseStatsMap[StatName] * Multiplier;
		else
			StatsMap[StatName] *= Multiplier;
	
		OnStatChanged.Broadcast(StatName, StatsMap[StatName]);
	}

	OutStat = StatsMap[StatName];

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	TimerDelegate.BindUFunction(this, FName("ResetStatToPreviousValue"), StatName, PrevValue); 
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Duration,false);
}

void UStatManagerComponent::IncreaseStatPercentageForDuration(FName StatName, float Percentage, bool UseBaseStat,
	float Duration, float &OutStat)
{
	float PrevValue;
	if (StatsMap.Contains(StatName))
	{
		PrevValue = StatsMap[StatName];
		if (UseBaseStat)
			StatsMap[StatName] += BaseStatsMap[StatName] * (Percentage / 100.0f);
		else
			StatsMap[StatName] += StatsMap[StatName] * (Percentage / 100.0f);
	
		OnStatChanged.Broadcast(StatName, StatsMap[StatName]);
	}
	
	OutStat = StatsMap[StatName];
	
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	TimerDelegate.BindUFunction(this, FName("ResetStatToPreviousValue"), StatName, PrevValue); 
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Duration,false);
}

void UStatManagerComponent::ResetStatToPreviousValue(FName StatName, float PreviousValue)
{
	if (StatsMap.Contains(StatName))
		StatsMap[StatName] = PreviousValue;
	
}

