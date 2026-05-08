// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiePlayerState.h"
#include "Net/UnrealNetwork.h"

void AZombiePlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZombiePlayerState, PlayerPoints);
}
