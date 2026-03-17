// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSUtils.h"
#include "GameManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStart, int, RoundCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundEnd, int, RoundCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyKilled, AActor*, Killer, EDamageType, DamageType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable,BlueprintType )
class ZOMBIEFPS_API UGameManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	UPROPERTY(BlueprintReadWrite)
	int CurrentRound=1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RoundHealthMultiplier = 1.1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int EnemyHealth = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int EnemyCount = 6;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int AliveEnemies;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RoundStartDelay=2.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxConcurrentEnemies = 24;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SpawnDelay=0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MinSpawnDelay=0.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxSpawnDelay=2;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> SpawnPoints;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> EnemyClass;

	UPROPERTY()
	int TotalSpawnedEnemies=0;
	
	UPROPERTY()
	FTimerHandle RoundStartTimer;
	
	UPROPERTY()
	FTimerHandle SpawnEnemyTimer;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> SpawnPointClass;
	
	UPROPERTY(BlueprintAssignable)
	FOnRoundStart OnRoundStart;
	
	UPROPERTY(BlueprintAssignable)
	FOnRoundEnd OnRoundEnd;
	
	UPROPERTY(BlueprintAssignable)
	FOnEnemyKilled OnEnemyKilled;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DropRate=2.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxDropsPerRound = 4;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AActor>> PossibleDrops;
	
	//This is to make sure that every drop is dropped before getting a duplicate
	UPROPERTY()
	TArray<TSubclassOf<AActor>> RemainingDrops;
	
	UPROPERTY()
	int DropNumber;
	
	UFUNCTION(BlueprintCallable)
	void SpawnDrop(FTransform SpawnPoint);
	
	UFUNCTION(BlueprintCallable)
	void ResetDrops();
	
	
	UFUNCTION(BlueprintCallable)
	void StartRound();
	
	UFUNCTION(BlueprintCallable)
	void EndRound();
	
	UFUNCTION(BlueprintCallable)
	void IncreaseRound();
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void StartSpawning();
	
	UFUNCTION()
	void CheckForEnemies(AActor* Killer, EDamageType DamageType);
};
