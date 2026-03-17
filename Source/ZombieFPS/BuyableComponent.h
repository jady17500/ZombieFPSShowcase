// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuyableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuyComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuyLimitReached);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable,BlueprintType )
class ZOMBIEFPS_API UBuyableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuyableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Price;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bHasLimitedBuyCount;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition="bHasLimitedBuyCount",EditConditionHides))
	int BuyCount=1;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FName RequiredCurrencyName;
	
	UPROPERTY(BlueprintAssignable)
	FOnBuyComplete OnBuyComplete;
	
	UPROPERTY(BlueprintAssignable)
	FOnBuyLimitReached OnBuyLimitReached;
	
	UFUNCTION(BlueprintCallable)
	void Buy(UCurrencyComponent* CurrencyComponent);
		
};
