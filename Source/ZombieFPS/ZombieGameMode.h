// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ZombieGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetListUpdated);

/**
 * 
 */
UCLASS()
class ZOMBIEFPS_API AZombieGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<AActor*> ZombieTargets;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<APawn*> Players;
	
	UPROPERTY(BlueprintAssignable)
	FOnTargetListUpdated OnTargetListUpdated;
	
	UFUNCTION(BlueprintCallable)
	void AddTarget(AActor* NewTarget);
	
	UFUNCTION(BlueprintCallable)
	void RemoveTarget(AActor* Target);
	
	UFUNCTION(BlueprintCallable)
	AActor* GetHighestPriorityTarget(AActor* Caller, FVector& OutLocation);
	
	UFUNCTION(BlueprintCallable)
	void UpdateTargetList();
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
