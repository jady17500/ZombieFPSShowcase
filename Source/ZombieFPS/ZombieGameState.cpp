// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieGameState.h"

#include "EnemyTargetComponent.h"
#include "Net/UnrealNetwork.h"

void AZombieGameState::Multicast_UpdateCurrentRound_Implementation()
{
	OnStartRoundRep.Broadcast(CurrentRound);
}

void AZombieGameState::Multicast_StartRoundTransition_Implementation()
{
	OnEndRoundRep.Broadcast(CurrentRound);
}

void AZombieGameState::Multicast_AddPlayer_Implementation(APlayerController* PlayerController)
{
	AlivePlayers.Add(PlayerController);
	OnPlayerJoined.Broadcast(PlayerController);
}

void AZombieGameState::Multicast_RemovePlayer_Implementation(APlayerController* PlayerController)
{
	AlivePlayers.Remove(PlayerController);
	OnPlayerLeft.Broadcast(PlayerController);

}

void AZombieGameState::Multicast_GameOver_Implementation()
{
	OnGameOver.Broadcast();
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Emerald,TEXT("Game Over"));
}


void AZombieGameState::Server_RemoveAlivePlayers_Implementation(APlayerController* PlayerController)
{
	if (AlivePlayers.Contains(PlayerController)){
		AlivePlayers.Remove(PlayerController);
		if (IsValid(PlayerController->GetPawn()))
			PlayerController->GetPawn()->GetComponentByClass<UEnemyTargetComponent>()->ChangePriority(0);
	}	
	if (AlivePlayers.Num() == 0)
		Multicast_GameOver();
}

void AZombieGameState::AddAlivePlayers(APlayerController* PlayerController)
{
	if (!AlivePlayers.Contains(PlayerController)){
		AlivePlayers.Add(PlayerController);
		if (IsValid(PlayerController->GetPawn()))
			PlayerController->GetPawn()->GetComponentByClass<UEnemyTargetComponent>()->ChangePriority(1);
	}	
}

void AZombieGameState::OnRep_CurrentRound()
{
	OnStartRoundRep.Broadcast(CurrentRound);
}

void AZombieGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZombieGameState, AlivePlayers);
	DOREPLIFETIME(AZombieGameState, CurrentRound);
	DOREPLIFETIME(AZombieGameState, Players);
}
