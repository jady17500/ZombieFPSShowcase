// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPSUtils.h"
#include "ShootComponent.generated.h"

class UCameraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBulletHit, FHitResult, hit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShoot);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),BlueprintType, Blueprintable )
class ZOMBIEFPS_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* MuzzleMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Global Settings")
	float MaxRange = 50000;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Global Settings")
	float SpreadMultiplier = 1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Global Settings")
	float Spread = 0.5f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Global Settings")
	bool bShootFromMuzzle;

	UPROPERTY(BlueprintAssignable)
	FOnShoot OnShootDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnBulletHit OnBulletHitDelegate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Global Settings")
	int MagazineAmmo = 30;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Global Settings")
	int ReserveAmmo = 60;

	UPROPERTY()
	int MaxReserveAmmo;
	
	UPROPERTY(BlueprintReadWrite)
	int CurrentAmmo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Global Settings")
	bool bInfiniteAmmo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing Settings")
	TArray<FiringMode> FiringModes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Settings")
	ProjectileType ProjectileType = ProjectileType::HITSCAN;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Firing Settings" ,meta=(EditCondition="FiringModes.Contains(FiringMode::BURST)" , EditConditionHides))
	int BurstCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Settings",meta=(EditCondition="ProjectileType==ProjectileType::BUCKSHOT" , EditConditionHides))
	int BuckShotCount;
	
	UPROPERTY(EditAnywhere, Blueprintable, Category="Projectile Settings", meta=(EditCondition="ProjectileType==ProjectileType::PROJECTILE" , EditConditionHides))
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(BlueprintReadWrite)
	FiringMode CurrentFiringMode;
	
	UFUNCTION(BlueprintCallable)
	void Shoot(FVector Start);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanShoot();

	UFUNCTION(BlueprintCallable)
	void Reload();
	
	UFUNCTION(BlueprintCallable)
	FHitResult ShootHitScan(FVector Start);
	
	UFUNCTION(BlueprintCallable)
	void ChangeFiringMode();
	
	UFUNCTION(BlueprintCallable)
	void RefillAmmo();
	
	TObjectPtr<AActor> ShootProjectile(FVector Start);

private:
	UPROPERTY()
	int FiringModeIndex;	
};
