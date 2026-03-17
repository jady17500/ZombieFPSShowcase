// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionStackComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionAdded, UObject*, NewAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionRemoved, UObject*, RemovedAction);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class ZOMBIEFPS_API UActionStackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionStackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UObject*> ActionStack;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<UObject*> FirstTimeActions;
	
	UPROPERTY(BlueprintReadWrite)
	UObject* CurrentAction;

	UPROPERTY(BlueprintAssignable)
	FOnActionAdded OnActionAdded;

	UPROPERTY(BlueprintAssignable)
	FOnActionRemoved OnActionRemoved;
	
	UFUNCTION(BlueprintCallable)
	void PushAction(UObject* Action);
	
	UFUNCTION(BlueprintCallable)
	void PopAction();
	
	UFUNCTION(BlueprintCallable)
	bool ValidateAction(UObject* Action);
	
	UFUNCTION(BlueprintCallable)
	void UpdateActions(float DeltaTime);
};
