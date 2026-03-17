// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyableComponent.h"
#include "CurrencyComponent.h"

// Sets default values for this component's properties
UBuyableComponent::UBuyableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuyableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuyableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuyableComponent::Buy(UCurrencyComponent* CurrencyComponent)
{
	if (!IsValid(CurrencyComponent)) return;
	if (BuyCount < 1 && bHasLimitedBuyCount) return;
	if (CurrencyComponent->CurrencyName != RequiredCurrencyName) return;
	
	if (CurrencyComponent->SpendCurrency(Price))
	{
		OnBuyComplete.Broadcast();
		if (BuyCount == 0)
			OnBuyLimitReached.Broadcast();
		else if (bHasLimitedBuyCount)
			BuyCount--;
	}
}

