// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetHealth(int NewHealth)
{
	CurrentHealth = NewHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}

void UHealthComponent::Heal(int HealAmount)
{
	if (bIsDead) return;
	
	CurrentHealth += HealAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
	OnHeathChanged.Broadcast(CurrentHealth);
	OnHeal.Broadcast();
}

void UHealthComponent::Damage(int Damage, AActor* Attacker, EDamageType DamageType)
{
	CurrentHealth -= Damage;
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,FString::Printf(TEXT("Damage %d"), Damage));
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
	OnHeathChanged.Broadcast(CurrentHealth);
	OnDamageTaken.Broadcast(Attacker, DamageType);
	
	if (CurrentHealth <= 0 && !bIsDead)
		Death(Attacker, DamageType);
}

void UHealthComponent::Death(AActor* Killer, EDamageType DamageType)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("Death"));
	if (!bIsDead)
		OnDeath.Broadcast(Killer, DamageType);
	bIsDead = true;
}

