// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"

#include "HealthComponent.h"
#include "StatManagerComponent.h"
#include "ZombieMultiplayerController.h"
#include "ZombieUtilities.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineAmmo;
	MaxReserveAmmo= ReserveAmmo;
	if (FiringModes.IsEmpty())
	{
		FiringModes.Add(FiringMode::AUTO);
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, "FIRING MODES EMPTY: ADDED FULL AUTO MODE");
	}
	CurrentFiringMode = FiringModes[0];
	FiringModeIndex = 0;
	
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void UShootComponent::Shoot(FVector Start)
{
	
	switch (ProjectileType) {
	case ProjectileType::HITSCAN:
		CurrentAmmo -= 1;
		ShootHitScan(Start);
		break;
	case ProjectileType::PROJECTILE:
		CurrentAmmo -= 1;
		ShootProjectile(Start);
		break;
	case ProjectileType::BUCKSHOT:
		CurrentAmmo-=1;
		for (int i = 0;i<BuckShotCount;i++)
			ShootHitScan(Start);
		break;
	}
	OnShootDelegate.Broadcast();
}

bool UShootComponent::CanShoot()
{
	return CurrentAmmo > 0;
}

void UShootComponent::Reload()
{
	if (bInfiniteAmmo)
	{
		CurrentAmmo = MagazineAmmo;
		
	}
	else
	{
		int difference = MagazineAmmo - CurrentAmmo;
		if (difference<ReserveAmmo)
		{
			CurrentAmmo = MagazineAmmo;
			ReserveAmmo -= difference;
		}
		else
		{
			CurrentAmmo+=ReserveAmmo;
			ReserveAmmo = 0;
		}
	}
}

FHitResult UShootComponent::ShootHitScan(FVector Start)
{
	FVector Location;
	FRotator Rotation;
	
	TObjectPtr<AZombieMultiplayerController> PC = Cast<AZombieMultiplayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->GetPlayerViewPoint(Location,Rotation);

	if (!bShootFromMuzzle)
		Start = Location;
	
	
	if (IsValid(GetOwner()->GetComponentByClass<UStatManagerComponent>()))
		GetOwner()->GetComponentByClass<UStatManagerComponent>()->GetStat("Spread", Spread);
	
	FVector EndLocation = Start + UKismetMathLibrary::RandomUnitVectorInConeInDegrees(Rotation.Vector(), Spread*SpreadMultiplier) *MaxRange;

	FHitResult Hit;
	ETraceTypeQuery TraceType = TraceTypeQuery1;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	ActorsToIgnore.Add(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, EndLocation, TraceType, false, ActorsToIgnore, EDrawDebugTrace::ForDuration,Hit, true, FLinearColor::Red, FLinearColor::Green, 0.5);
	
	if (IsValid(Hit.GetActor()))
	{
		if (IsValid(Hit.GetActor()->GetComponentByClass<UHealthComponent>()))
		{
			float Damage = 0;
			float DamageMultiplier = 1;
			float BonusMultiplier = 1;
			if (!UZombieUtilities::RequestStatFromActor(GetOwner()->GetOwner(), "DamageMultiplier", false, BonusMultiplier))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "DamageMultiplier NOT FOUND");
				BonusMultiplier = 1;
			}
			
			EDamageType DamageType = EDamageType::BODYSHOT;
			
			if (GetOwner()->GetComponentByClass<UStatManagerComponent>()->GetStat("Damage", Damage))
			{
				
				if (Hit.PhysMaterial->SurfaceType == SurfaceType1)
				{
					GetOwner()->GetComponentByClass<UStatManagerComponent>()->GetStat("HeadshotMultiplier", DamageMultiplier);
					DamageType = EDamageType::HEADSHOT;
				}
				
				else if (Hit.PhysMaterial->SurfaceType == SurfaceType2)
				{
					GetOwner()->GetComponentByClass<UStatManagerComponent>()->GetStat("BodyshotMultiplier", DamageMultiplier);
					DamageType = EDamageType::BODYSHOT;
				}
				
				else if (Hit.PhysMaterial->SurfaceType == SurfaceType3)
				{
					GetOwner()->GetComponentByClass<UStatManagerComponent>()->GetStat("LegshotMultiplier", DamageMultiplier);
					DamageType = EDamageType::BODYSHOT;
				}
				
				Damage*=DamageMultiplier;
				Damage*=BonusMultiplier;
				PC->Server_Damage(Hit.GetActor(), FMath::FloorToInt(Damage), DamageType);
				//Hit.GetActor()->GetComponentByClass<UHealthComponent>()->Damage(FMath::FloorToInt(Damage), UGameplayStatics::GetPlayerPawn(GetWorld(),0), DamageType);
			}
			else
				GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, "INVALID DAMAGE CHECK WEAPON STAT MANAGER");
		}
		OnBulletHitDelegate.Broadcast(Hit);
	}
	return Hit;
}

void UShootComponent::ChangeFiringMode()
{
	if (FiringModes.Num() == 1) return;
	FiringModeIndex++;
	if (FiringModeIndex > FiringModes.Num()-1)
		FiringModeIndex = 0;
	
	CurrentFiringMode = FiringModes[FiringModeIndex];
	
}

void UShootComponent::RefillAmmo()
{
	ReserveAmmo = MaxReserveAmmo;
	CurrentAmmo = MagazineAmmo;
}

TObjectPtr<AActor> UShootComponent::ShootProjectile(FVector Start)
{
	FVector Location;
	FRotator Rotation;
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(Location,Rotation);

	if (!bShootFromMuzzle)
		Start = Location;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	
	TObjectPtr<AActor> Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, Start, Rotation, SpawnParams);
	
	return Projectile;
	
}

void UShootComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UShootComponent, MaxReserveAmmo)
	DOREPLIFETIME(UShootComponent, CurrentAmmo)
	DOREPLIFETIME(UShootComponent, ReserveAmmo)
	DOREPLIFETIME(UShootComponent, MagazineAmmo)
}




