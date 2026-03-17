// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CurrencyComponent.generated.h"

class UStatManagerComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrencyGained,int,Amount,int, CurrentBalance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrencySpent,int,Amount,int, CurrentBalance);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),BlueprintType, Blueprintable )
class ZOMBIEFPS_API UCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCurrencyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName CurrencyName;
	
	UPROPERTY(BLueprintReadWrite, EditAnywhere)
	int StartAmount=0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CurrencyAmount=0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsCapped = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(EditCondition="bIsCapped",EditConditionHides));
	int MaxCurrencyAmount=0;
	
	UPROPERTY(BlueprintAssignable)
	FOnCurrencyGained OnCurrencyGained;
	
	UPROPERTY(BlueprintAssignable)
	FOnCurrencySpent OnCurrencySpent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName CurrencyMultiplierKey;
	
	UPROPERTY()
	UStatManagerComponent* StatManagerComponent;
	
	UFUNCTION(BlueprintCallable)
	virtual void GainCurrency(int Amount);
	
	UFUNCTION(BlueprintCallable)
	virtual bool SpendCurrency(int Amount);
		
};
