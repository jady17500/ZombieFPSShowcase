// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZombieUtilities.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEFPS_API UZombieUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Stats")
	static bool RequestStatFromActor(AActor* Actor, FName StatName, bool UseBase, float &OutStat);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Match")
	static bool GetCurrentRound(int &OutRound);
};
