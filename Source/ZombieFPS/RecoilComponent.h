// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecoilComponent.generated.h"

class UCameraComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class ZOMBIEFPS_API URecoilComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecoilComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalRecoilMin = 0.2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalRecoilMax = 0.4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalRecoilInterpSpeed = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float VerticalRecoilRecoveryInterpSpeed = 8.0f;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalRecoilMin = -0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HorizontalRecoilMax = 0.1;

	UPROPERTY()
	float RecoilRecoveryVertical = 0;

	UPROPERTY()
	float RecoilRecoveryHorizontal = 0;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	float CurrentRecoilVertical;
	float CurrentRecoilHorizontal;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ApplyRecoil();
};
