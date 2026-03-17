// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PerkComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType, Blueprintable )
class ZOMBIEFPS_API UPerkComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPerkComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FSlateBrush PerkIconBrush;
	
	UFUNCTION(BlueprintCallable)
	virtual void PerkStart();
	
	UFUNCTION(BlueprintCallable)
	virtual void PerkRemove();
	
	UFUNCTION(BlueprintCallable)
	virtual void PerkTick(float DeltaSeconds);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PerkStartEvent();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PerkRemoveEvent();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PerkTickEvent(float DeltaSeconds);
		
};
