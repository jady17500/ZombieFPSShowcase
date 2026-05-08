// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnZoneManagerComponent.generated.h"

class ASpawnZoneVolume;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class ZOMBIEFPS_API USpawnZoneManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnZoneManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<ASpawnZoneVolume*> SpawnZoneVolumes;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<ASpawnZoneVolume*> ActiveZones;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetValidSpawnPoint(AActor*& OutActor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetSpawnPoint(AActor*& OutActor);
	
	UFUNCTION(BlueprintCallable)
	void CheckActiveZoneExit(ASpawnZoneVolume* Zone);

	UFUNCTION(BlueprintCallable)
	void CheckActiveZoneEnter(ASpawnZoneVolume* Zone);
};
