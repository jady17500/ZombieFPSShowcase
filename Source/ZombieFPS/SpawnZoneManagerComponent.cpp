// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnZoneManagerComponent.h"

#include "SpawnZoneVolume.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnZoneManagerComponent::USpawnZoneManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnZoneManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> ZoneActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ASpawnZoneVolume::StaticClass(), ZoneActors);

	for (auto Actor : ZoneActors)
		SpawnZoneVolumes.Add(Cast<ASpawnZoneVolume>(Actor));

	for (auto Zone : SpawnZoneVolumes)
	{
		Zone->OnZoneEntered.AddDynamic(this, &USpawnZoneManagerComponent::CheckActiveZoneEnter);
		Zone->OnZoneExit.AddDynamic(this, &USpawnZoneManagerComponent::CheckActiveZoneExit);
	}
}


// Called every frame
void USpawnZoneManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USpawnZoneManagerComponent::GetValidSpawnPoint(AActor*& OutActor)
{
	if (ActiveZones.Num() <= 0) return false;

	if (!ActiveZones[FMath::RandRange(0,ActiveZones.Num()-1)]->GetSpawnPoint(OutActor))
		return false;
	
	return true;
}

void USpawnZoneManagerComponent::GetSpawnPoint(AActor*& OutActor)
{
	SpawnZoneVolumes[FMath::RandRange(0,SpawnZoneVolumes.Num()-1)]->GetSpawnPoint(OutActor);
}


void USpawnZoneManagerComponent::CheckActiveZoneExit(ASpawnZoneVolume* Zone)
{
	if (Zone->PlayerCount <= 0 && ActiveZones.Contains(Zone) )
	{
		ActiveZones.Remove(Zone);
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Removed Zone");
	}
	
}

void USpawnZoneManagerComponent::CheckActiveZoneEnter(ASpawnZoneVolume* Zone)
{
	if (!ActiveZones.Contains(Zone))
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,"Added Zone");
		ActiveZones.Add(Zone);
	}
}




