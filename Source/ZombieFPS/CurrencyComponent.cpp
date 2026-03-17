// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrencyComponent.h"
#include "StatManagerComponent.h"

// Sets default values for this component's properties
UCurrencyComponent::UCurrencyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrencyAmount = StartAmount;
	StatManagerComponent = GetOwner()->GetComponentByClass<UStatManagerComponent>();
	if (!IsValid(StatManagerComponent))
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red, "INVALID STAT MANAGER");
	// ...
}


void UCurrencyComponent::GainCurrency(int Amount)
{
	float Multiplier =0; 
	StatManagerComponent->GetStat(CurrencyMultiplierKey, Multiplier);
	CurrencyAmount += Amount*Multiplier;
	if (bIsCapped)
		CurrencyAmount = FMath::Clamp(CurrencyAmount, 0, MaxCurrencyAmount);
	
	OnCurrencyGained.Broadcast(Amount*Multiplier, CurrencyAmount);
}

bool UCurrencyComponent::SpendCurrency(int Amount)
{
	if (CurrencyAmount >= Amount)
	{
		CurrencyAmount -= Amount;
		OnCurrencySpent.Broadcast(Amount, CurrencyAmount);
		return true;
	}
	return false;
}

// Called every frame
void UCurrencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

