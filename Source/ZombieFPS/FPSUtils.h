// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class FiringMode : uint8 {
	SINGLE = 0 UMETA(DisplayName = "SingleFire"),
	AUTO = 1  UMETA(DisplayName = "FullAuto"),
	BURST = 2     UMETA(DisplayName = "BurstFire"),
};

UENUM(BlueprintType)
enum class ProjectileType : uint8 {
	HITSCAN = 0 UMETA(DisplayName = "HitScan"),
	PROJECTILE = 1  UMETA(DisplayName = "Projectile"),
	BUCKSHOT = 2     UMETA(DisplayName = "Buckshot"),
};

UENUM(BLueprintType)
enum class EDamageType : uint8
{
	HEADSHOT = 0 UMETA(DisplayName = "Headshot"),
	BODYSHOT = 1 UMETA(DisplayName = "Bodyshot"),
	MELEE = 2 UMETA(DisplayName = "Melee"),
};
/**
 * 
 */
class ZOMBIEFPS_API FPSUtils
{
public:
	FPSUtils();
	~FPSUtils();
};
