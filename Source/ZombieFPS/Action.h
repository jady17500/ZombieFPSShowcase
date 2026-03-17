// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Action.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UAction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBIEFPS_API IAction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnStart(bool bIsFirstTime);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEnd();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdate(float DeltaTime);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsDone();
};
