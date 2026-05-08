// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
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
	OnHeathChanged.Broadcast(CurrentHealth);
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
	OnPreDamage.Broadcast(Attacker,DamageType,Damage);
	CurrentHealth -= Damage;
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,FString::Printf(TEXT("Damage %d"), Damage));
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
	OnHeathChanged.Broadcast(CurrentHealth);
	OnDamageTaken.Broadcast(Attacker, DamageType);
	
	if (CurrentHealth <= 0 && !bIsDead)
		Server_Death(Attacker, DamageType);
}

void UHealthComponent::Server_Death_Implementation(AActor* Killer, EDamageType DamageType)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("Server Death"));
	Multicast_Death(Killer, DamageType);
}

void UHealthComponent::Multicast_Death_Implementation(AActor* Killer, EDamageType DamageType)
{
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,TEXT("Multicast Death"));
	if (!bIsDead)
		OnDeath.Broadcast(Killer, DamageType);
	bIsDead = true;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
	DOREPLIFETIME(UHealthComponent, bIsDead);
}

