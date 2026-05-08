// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerComponent.h"
#include "HealthComponent.h"
#include "SpawnZoneManagerComponent.h"
#include "ZombieGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UGameManagerComponent::UGameManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGameManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	GameState = Cast<AZombieGameState>(UGameplayStatics::GetGameState(GetWorld()));
	OnEnemyKilled.AddDynamic(this, &UGameManagerComponent::CheckForEnemies);
	if (!GetOwner()->GetComponentByClass<USpawnZoneManagerComponent>())
		GetOwner()->AddComponentByClass(USpawnZoneManagerComponent::StaticClass(), false, FTransform::Identity, false);

	SpawnZoneManager = GetOwner()->GetComponentByClass<USpawnZoneManagerComponent>();
	
	StartRound();
	ResetDrops();
}


// Called every frame
void UGameManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGameManagerComponent::SpawnDrop(FTransform SpawnPoint)
{
	if (!UKismetMathLibrary::RandomBoolWithWeight(DropRate/100)) return;
	if (DropNumber<=0) return;
	DropNumber--;
	FActorSpawnParameters SpawnParams;
	if (RemainingDrops.Num() == 0)
		ResetDrops();
	
	TSubclassOf<AActor> DropClass = RemainingDrops[FMath::RandRange(0,RemainingDrops.Num()-1)];
	GetWorld()->SpawnActor<AActor>(DropClass,SpawnPoint,SpawnParams);
	
	PossibleDrops.Remove(DropClass);
}

void UGameManagerComponent::ResetDrops()
{
	RemainingDrops = PossibleDrops;
}

void UGameManagerComponent::StartRound()
{
	DropNumber=MaxDropsPerRound;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Round: %d"), CurrentRound));
	GameState->CurrentRound = CurrentRound;
	OnRoundStart.Broadcast(CurrentRound);
	
	GameState->Multicast_UpdateCurrentRound();
	StartSpawning();
}

void UGameManagerComponent::EndRound()
{
	OnRoundEnd.Broadcast(CurrentRound);
	GameState->Multicast_StartRoundTransition();
	IncreaseRound();
	GetWorld()->GetTimerManager().SetTimer(RoundStartTimer,this ,&UGameManagerComponent::StartRound, RoundStartDelay,false);
}

void UGameManagerComponent::IncreaseRound()
{
	CurrentRound++;
	EnemyCount+=CurrentRound;
	EnemyHealth*=RoundHealthMultiplier;
	TotalSpawnedEnemies=0;
}

void UGameManagerComponent::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	AActor* SpawnPointActor= nullptr;
	FTransform SpawnTransform = FTransform::Identity;
	if (SpawnZoneManager->GetValidSpawnPoint(SpawnPointActor))
		SpawnTransform = SpawnPointActor->GetActorTransform();
	else
	{
		SpawnZoneManager->GetSpawnPoint(SpawnPointActor);
		SpawnTransform = SpawnPointActor->GetActorTransform();
	}
	TObjectPtr<AActor> Enemy = GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnTransform);
		
	if (EnemyHealth == 0)
		EnemyHealth = Enemy->GetComponentByClass<UHealthComponent>()->MaxHealth;

	if (!IsValid(Enemy)) return;
	
	Enemy->GetComponentByClass<UHealthComponent>()->MaxHealth = EnemyHealth;
	Enemy->GetComponentByClass<UHealthComponent>()->SetHealth(EnemyHealth);
	Enemy->GetComponentByClass<UHealthComponent>()->OnDeath.AddDynamic(this, &UGameManagerComponent::CheckForEnemies);
	AliveEnemies++;
	TotalSpawnedEnemies++;
	StartSpawning();
}

void UGameManagerComponent::StartSpawning()
{
	if (AliveEnemies < MaxConcurrentEnemies && TotalSpawnedEnemies < EnemyCount)
	{
		SpawnDelay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);
		GetWorld()->GetTimerManager().SetTimer(SpawnEnemyTimer, this, &UGameManagerComponent::SpawnEnemy, SpawnDelay, false);
	}
}

void UGameManagerComponent::CheckForEnemies(AActor* Killer, EDamageType DamageType)
{
	AliveEnemies--;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Zombies: %d"), AliveEnemies));
	if (AliveEnemies == 0 && TotalSpawnedEnemies >= EnemyCount)
		EndRound();
	else
		StartSpawning();
		
}

