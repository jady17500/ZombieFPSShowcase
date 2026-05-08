// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "SpawnZoneVolume.generated.h"

/**
 * 
 */


DECLARE_DELEGATE(FCheckForPlayers);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZoneEntered, ASpawnZoneVolume*, Zone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZoneExit, ASpawnZoneVolume*, Zone);
UCLASS(Blueprintable,BlueprintType)
class ZOMBIEFPS_API ASpawnZoneVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:
	ASpawnZoneVolume();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetSpawnPoint(AActor*& OutActor);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PlayerCount=0;
	
	UPROPERTY(BlueprintAssignable)
	FOnZoneEntered OnZoneEntered;

	UPROPERTY(BlueprintAssignable)
	FOnZoneExit OnZoneExit;
	
	UFUNCTION(BlueprintCallable)
	void CheckForSpawnPoints();
	
	UFUNCTION(BlueprintCallable)
	void CheckForPlayers();
};
