// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieGameMode.h"

#include "EnemyTargetComponent.h"
#include "ZombieGameState.h"
#include "Kismet/KismetMathLibrary.h"

void AZombieGameMode::AddTarget(AActor* NewTarget)
{
	if (!IsValid(NewTarget)) return;
	if (ZombieTargets.Contains(NewTarget)) return;
	
	ZombieTargets.Add(NewTarget);
	NewTarget->GetComponentByClass<UEnemyTargetComponent>()->OnPriorityChanged.AddDynamic(this, &AZombieGameMode::UpdateTargetList);
	OnTargetListUpdated.Broadcast();
}

void AZombieGameMode::RemoveTarget(AActor* Target)
{
	if (!IsValid(Target)) return;
	if (!ZombieTargets.Contains(Target)) return;
	
	ZombieTargets.Remove(Target);
	Target->GetComponentByClass<UEnemyTargetComponent>()->OnPriorityChanged.RemoveDynamic(this, &AZombieGameMode::UpdateTargetList);
	OnTargetListUpdated.Broadcast();
}

AActor* AZombieGameMode::GetHighestPriorityTarget(AActor* Caller, FVector& OutLocation)
{
	if (ZombieTargets.Num() == 0) return nullptr;
	
	int Priority = 0;
	for (int i = 0; i < ZombieTargets.Num(); i++)
	{
		if (ZombieTargets[i]->GetComponentByClass<UEnemyTargetComponent>()->PriorityLevel > Priority)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Target found"));
			Priority = ZombieTargets[i]->GetComponentByClass<UEnemyTargetComponent>()->PriorityLevel;
		}
	}
	TArray<AActor*> PossibleTargets;
	
	for (int i = 0; i < ZombieTargets.Num(); i++)
	{
		if (ZombieTargets[i]->GetComponentByClass<UEnemyTargetComponent>()->PriorityLevel == Priority)
			PossibleTargets.Add(ZombieTargets[i]);
		
	}
	
	double Distance = 0.0f;
	int Index = 0;
	for (int i = 0; i < PossibleTargets.Num(); i++)
	{
		double d = UKismetMathLibrary::Vector_Distance(Caller->GetActorLocation(), PossibleTargets[i]->GetActorLocation());
		if (d < Distance || Distance == 0)
		{
			Distance = d;
			Index = i;
		}
	}
	
	if (Priority <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("No target found"));
		return nullptr;
	}
	
	return PossibleTargets[Index];
	
}

void AZombieGameMode::UpdateTargetList()
{
	OnTargetListUpdated.Broadcast();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("UpdateTargetList"));
}

void AZombieGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	AZombieGameState* ZombieState = Cast<AZombieGameState>(GameState);
	ZombieState->Multicast_AddPlayer(NewPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Player joined"));
}

void AZombieGameMode::Logout(AController* Exiting)
{
	AZombieGameState* ZombieState = Cast<AZombieGameState>(GameState);
	ZombieState->Server_RemoveAlivePlayers(Cast<APlayerController>(Exiting));
	ZombieState->Multicast_RemovePlayer(Cast<APlayerController>(Exiting));
	Super::Logout(Exiting);
}
