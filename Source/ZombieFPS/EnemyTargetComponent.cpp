// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTargetComponent.h"

#include "ZombieGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyTargetComponent::UEnemyTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	Server_AddTarget();
	
	// ...
	
}


// Called every frame
void UEnemyTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEnemyTargetComponent::ChangePriority(int NewPriority)
{
	Server_ChangePriority(NewPriority);
}

void UEnemyTargetComponent::Server_ChangePriority_Implementation(int NewPriority)
{
	Multicast_ChangePriority(NewPriority);
}

void UEnemyTargetComponent::Multicast_ChangePriority_Implementation(int NewPriority)
{
	PriorityLevel = NewPriority;
	OnPriorityChanged.Broadcast();
}

void UEnemyTargetComponent::Server_AddTarget_Implementation()
{
	if (Cast<AZombieGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("Target Added"));
		Cast<AZombieGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddTarget(GetOwner());
	}
	
}

void UEnemyTargetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (Cast<AZombieGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		Cast<AZombieGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->RemoveTarget(GetOwner());
}

