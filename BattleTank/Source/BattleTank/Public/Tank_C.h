// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
//#include "Projectile_C.h"
#include "Tank_C.generated.h" // Put All includes above 

// Forward Declaration
class AProjectile_C;
class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret_C;  // The thanks of UFUNCTION(BlueprintCallable... "Tank_C.generated.h" automaticly forwrd declaring this class  but without UFUNCTION(BlueprintCallable... we need this line
class UTankBarrel_C;  // The thanks of UFUNCTION(BlueprintCallable... "Tank_C.generated.h" automaticly forwrd declaring this class  but without UFUNCTION(BlueprintCallable... we need this line


UCLASS()
class BATTLETANK_API ATank_C : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank_C();

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

	UTankBarrel_C *Barrel = nullptr;  // Local barrel reference for spawning projectile


	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000; // TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup) // we need this class to get Projectile_BP in C++
		TSubclassOf<AProjectile_C> ProjectileBlueprint; // Alternative { UClass *ProjectileBueprint } and it's get all kind of classess But in our case it get only AProjectile_C or it's derived classess


protected:

	UTankAimingComponent *TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent *TankMovementComponent = nullptr;

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector, FString);

	UFUNCTION(BlueprintCallable, Category = Setup)  // for use in Blueprint
		void SetBarrelReference(UTankBarrel_C *BarrelToSet); // use function in Tank_BP  // UTankBarrel is derived from UStaticMashComponent

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret_C *TurretToSet);


	UFUNCTION(BlueprintCallable, Category = Setup)
		void Firing();


};