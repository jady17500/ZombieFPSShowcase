// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyTargetComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPriorityChanged);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class ZOMBIEFPS_API UEnemyTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyTargetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int PriorityLevel = 1;
	
	UPROPERTY(BlueprintAssignable)
	FOnPriorityChanged OnPriorityChanged;
	
	UFUNCTION(BlueprintCallable)
	void ChangePriority(int NewPriority);
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ChangePriority(int NewPriority);
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void Multicast_ChangePriority(int NewPriority);
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_AddTarget();
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
