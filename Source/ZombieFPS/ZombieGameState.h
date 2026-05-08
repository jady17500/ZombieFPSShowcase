// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ZombieGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartRoundRep, int, CurrentRound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndRoundRep, int, CurrentRound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined, APlayerController*, PlayerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLeft, APlayerController*, PlayerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);
UCLASS()
class ZOMBIEFPS_API AZombieGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<APlayerController*> AlivePlayers;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CurrentRound)
	int CurrentRound = 0;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	TArray<APlayerController*> Players;
	
	UPROPERTY(BlueprintAssignable)
	FOnStartRoundRep OnStartRoundRep;
	
	UPROPERTY(BlueprintAssignable)
	FOnEndRoundRep OnEndRoundRep;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerJoined OnPlayerJoined;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerLeft  OnPlayerLeft;
	
	UPROPERTY(BlueprintAssignable)
	FOnGameOver OnGameOver;
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Multicast_UpdateCurrentRound();
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Multicast_StartRoundTransition();
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Multicast_AddPlayer(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Multicast_RemovePlayer(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Multicast_GameOver();
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_RemoveAlivePlayers(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintCallable)
	void AddAlivePlayers(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintCallable)
	void OnRep_CurrentRound();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
