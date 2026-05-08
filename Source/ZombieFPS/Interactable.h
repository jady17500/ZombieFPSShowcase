// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZOMBIEFPS_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor* Interactor);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InteractOngoing(AActor* Interactor);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void InteractOver(AActor* Interactor);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetInteractText(FText &OutText, FText &OutDescription);
};
