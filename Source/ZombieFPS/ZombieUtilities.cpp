// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieUtilities.h"

#include "GameManagerComponent.h"
#include "StatManagerComponent.h"
#include "ZombieGameState.h"
#include "AI/NavigationSystemBase.h"
#include "GameFramework/GameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"


bool UZombieUtilities::RequestStatFromActor(AActor* Actor, FName StatName, bool UseBase, float& OutStat)
{
	if (!IsValid(Actor)) return false;
	if (!IsValid(Actor->GetComponentByClass<UStatManagerComponent>())) return false;

	UStatManagerComponent* StatManager = Actor->GetComponentByClass<UStatManagerComponent>();
	if (!StatManager->GetStat(StatName, OutStat)) return false;


	if (UseBase)
		StatManager->GetBaseStat(StatName, OutStat);
	else
		StatManager->GetStat(StatName, OutStat);
	
	return true;
	
	
}

bool UZombieUtilities::GetCurrentRound(int& OutRound)
{
	if(!IsValid(GEngine)) return false;
	if (!IsValid(GEngine->GameViewport)) return false;
	UWorld* World = GEngine->GameViewport->GetWorld();
	
	if (!IsValid(World)) return false;
	if (!Cast<AZombieGameState>(UGameplayStatics::GetGameState(World))) return false;
	
	OutRound = Cast<AZombieGameState>(UGameplayStatics::GetGameState(World))->CurrentRound;
	return true;
}
