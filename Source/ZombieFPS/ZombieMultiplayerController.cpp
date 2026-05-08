// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieMultiplayerController.h"
#include "HealthComponent.h"
#include "PlayerHealth.h"
#include "Kismet/GameplayStatics.h"

void AZombieMultiplayerController::Server_Damage_Implementation(AActor* ActorToDamage, int Damage,
                                                                EDamageType DamageType)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Controller Damage");
	ActorToDamage->GetComponentByClass<UHealthComponent>()->Damage(Damage, GetPawn(), DamageType);
	
}

void AZombieMultiplayerController::Server_AddReviveCharges_Implementation(AActor* ActorToRevive, float ReviveCharges)
{
	UPlayerHealth* PlayerHealth = ActorToRevive->GetComponentByClass<UPlayerHealth>();
	if (IsValid(PlayerHealth))
		PlayerHealth->Server_AddReviveCharges(ReviveCharges);
	
}
