// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSUtils.h"
#include "ZombieMultiplayerController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEFPS_API AZombieMultiplayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Server, Unreliable)
	virtual void Server_Damage(AActor* ActorToDamage, int Damage,EDamageType DamageType);
	
	UFUNCTION(BlueprintCallable, Server, Unreliable)
	virtual void Server_AddReviveCharges(AActor* ActorToRevive, float ReviveCharges);
};
