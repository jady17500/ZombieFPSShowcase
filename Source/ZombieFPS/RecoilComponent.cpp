// Fill out your copyright notice in the Description page of Project Settings.

#include "RecoilComponent.h"
#include "ShootComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
URecoilComponent::URecoilComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URecoilComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (GetOwner()->GetComponentByClass<UShootComponent>())
		GetOwner()->GetComponentByClass<UShootComponent>()->OnShootDelegate.AddDynamic(this , &URecoilComponent::ApplyRecoil);
	
}


// Called every frame
void URecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (IsValid(PlayerController))
	{
		CurrentRecoilVertical = FMath::FInterpTo(CurrentRecoilVertical, 0, DeltaTime,VerticalRecoilInterpSpeed);
		RecoilRecoveryVertical = FMath::FInterpTo(RecoilRecoveryVertical, -CurrentRecoilVertical, DeltaTime, VerticalRecoilRecoveryInterpSpeed);
		float ApplyPitch = (CurrentRecoilVertical + RecoilRecoveryVertical)*DeltaTime;
		
		PlayerController->AddPitchInput(ApplyPitch);
	}
}

void URecoilComponent::ApplyRecoil()
{
	CurrentRecoilHorizontal = FMath::FRandRange(HorizontalRecoilMin, HorizontalRecoilMax);
	CurrentRecoilVertical -= FMath::FRandRange(VerticalRecoilMin, VerticalRecoilMax);
}

