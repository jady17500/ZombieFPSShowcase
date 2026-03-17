// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealth.h"
#include "StatManagerComponent.h"

void UPlayerHealth::BeginPlay()
{
	Super::BeginPlay();
	OnDamageTaken.AddDynamic(this, &UPlayerHealth::CancelRegeneration);
	if (bUseStatManager)
		InitStats();
	
}

void UPlayerHealth::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UPlayerHealth::Regenerate()
{
	Heal(RegenerationRate);
	if (CurrentHealth>= MaxHealth)
		if(GetWorld()->GetTimerManager().IsTimerActive(RegenerationRateTimer))
			GetWorld()->GetTimerManager().ClearTimer(RegenerationRateTimer);
}

void UPlayerHealth::StartRegenerate()
{
	bCanRegenerate = true;
	GEngine->AddOnScreenDebugMessage(-1,5.0f, FColor::Red,"StartRegeneration");
	GetWorld()->GetTimerManager().SetTimer(RegenerationRateTimer,this, &UPlayerHealth::Regenerate,RegenerationTick,true);
}

void UPlayerHealth::UpdateHealth(FName StatKey, float OutStat)
{
	if (StatKey == HealthKey)
	{
		MaxHealth = OutStat;
		if (CurrentHealth < MaxHealth)
			StartRegenerate();
	}
}

void UPlayerHealth::UpdateRegeneration(FName StatKey, float OutStat)
{
	if (StatKey == RegenerationDelayKey)
		RegenerationDelay = OutStat;
	else if (StatKey == RegenerationRateKey)
		RegenerationRate = OutStat;
	else if (StatKey == RegenerationTickKey)
		RegenerationTick = OutStat;
}

void UPlayerHealth::CancelRegeneration(AActor* Attacker, EDamageType DamageType)
{
	bCanRegenerate = false;
	if(GetWorld()->GetTimerManager().IsTimerActive(RegenerationRateTimer))
		GetWorld()->GetTimerManager().ClearTimer(RegenerationRateTimer);
	
	if(GetWorld()->GetTimerManager().IsTimerActive(RegenerationDelayTimer))
		GetWorld()->GetTimerManager().ClearTimer(RegenerationDelayTimer);
	
	GetWorld()->GetTimerManager().SetTimer(RegenerationDelayTimer,this, &UPlayerHealth::StartRegenerate,RegenerationDelay,false);
}

void UPlayerHealth::InitStats()
{
	float OutHealth;
	float OutRegenerationRate;
	float OutRegenerationTick;
	float OutRegenerationDelay;
	UStatManagerComponent* StatManager = GetOwner()->GetComponentByClass<UStatManagerComponent>();
	if (IsValid(StatManager))
	{
		
		if (StatManager->GetStat(HealthKey, OutHealth))
			MaxHealth = FMath::FloorToInt(OutHealth);
		else
			StatManager->AddStat(HealthKey, MaxHealth);
		
		if (StatManager->GetStat(RegenerationRateKey, OutRegenerationRate))
			RegenerationRate = FMath::FloorToInt(OutRegenerationRate);
		else
			StatManager->AddStat(RegenerationRateKey, RegenerationRate);

		if (StatManager->GetStat(RegenerationTickKey, OutRegenerationTick))
			RegenerationTick = OutRegenerationTick;
		else
			StatManager->AddStat(RegenerationTickKey, RegenerationTick);

		if (StatManager->GetStat(RegenerationDelayKey, OutRegenerationDelay))
			RegenerationDelay = OutRegenerationDelay;
		else
			StatManager->AddStat(RegenerationDelayKey, RegenerationDelay);
		
		CurrentHealth = MaxHealth;
		StatManager->OnStatChanged.AddDynamic(this, &UPlayerHealth::UpdateRegeneration);
		StatManager->OnStatChanged.AddDynamic(this, &UPlayerHealth::UpdateHealth);
		
	}
}