// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Action.h"
#include "ActionWidget.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEFPS_API UActionWidget : public UUserWidget, public IAction
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	virtual void OnStart_Implementation(bool bIsFirstTime) override;
	virtual void OnUpdate_Implementation(float DeltaTime) override;
	virtual void OnEnd_Implementation() override;
	virtual bool IsDone_Implementation() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDone;
};
