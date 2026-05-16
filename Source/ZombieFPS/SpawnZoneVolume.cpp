// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnZoneVolume.h"

#include "PlayerHealth.h"
#include "SpawnPoint.h"
#include "Components/BrushComponent.h"
#include "Kismet/KismetSystemLibrary.h"


ASpawnZoneVolume::ASpawnZoneVolume()
{
	UBrushComponent* BrushComp = GetBrushComponent();

	BrushComp->SetVisibility(true);
	BrushComp->SetHiddenInGame(true);
}

void ASpawnZoneVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (OtherActor->GetComponentByClass<UPlayerHealth>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Player Enter Zone");
		PlayerCount++;
		OnZoneEntered.Broadcast(this);
	}
}

void ASpawnZoneVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (OtherActor->GetComponentByClass<UPlayerHealth>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Exit Zone");
		PlayerCount--;
		OnZoneExit.Broadcast(this);
	}
}

void ASpawnZoneVolume::BeginPlay()
{
	Super::BeginPlay();
	CheckForSpawnPoints();
	FTimerDelegate OnPlayerCheckDelegate;
	OnPlayerCheckDelegate.BindUFunction(this, FName("CheckForPlayers"));
	GetWorld()->GetTimerManager().SetTimerForNextTick(OnPlayerCheckDelegate);
}

bool ASpawnZoneVolume::GetSpawnPoint(AActor*& OutActor)
{
	if (SpawnPoints.Num() <= 0) return false;

	OutActor = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];
	return true;
}

void ASpawnZoneVolume::CheckForSpawnPoints()
{
	FVector Origin = GetActorLocation();
	FVector Bounds = FVector::ZeroVector;
	GetActorBounds(false,Origin,Bounds);
	const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes = {EObjectTypeQuery::ObjectTypeQuery7};
	TArray<AActor*> ActorToIgnore;
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), Origin,Bounds, ObjectTypes, ASpawnPoint::StaticClass(),ActorToIgnore, SpawnPoints);
}

void ASpawnZoneVolume::CheckForPlayers()
{
	FVector Origin = GetActorLocation();
	FVector Bounds = FVector::ZeroVector;
	GetActorBounds(false,Origin,Bounds);
	const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes = {EObjectTypeQuery::ObjectTypeQuery3};
	TArray<AActor*> ActorToIgnore;
	TArray<AActor*> Players;
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), Origin,Bounds, ObjectTypes, APawn::StaticClass(),ActorToIgnore, Players);
	
	if (Players.Num() > 0)
	{
		for (AActor* Player : Players)
		{
			if (Player->GetComponentByClass<UPlayerHealth>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Player Enter Zone");
				PlayerCount++;
				OnZoneEntered.Broadcast(this);
			}
		}
	}
}
