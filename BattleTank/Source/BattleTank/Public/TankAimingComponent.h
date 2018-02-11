// Copyright EmbraceIT Ltd.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//ENUM
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Forward Declaration
class UTankTurret_C;
class UTankBarrel_C;
class AProjectile_C;

UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel_C *BarrelToSet, UTankTurret_C *TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Firing();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundLeft() const;

	//void AimAt(FVector, FString, float); // FVector = HitObjectLocation FString = HitObjecName float = LaunchSpeed
	void AimAt(FVector, FString);
	void MoveBarrel();

	EFiringState GetFiringState() const;

protected:

	// we need this in protected category because it's called subclass TankAimingComponentBP in PlayerUI Widget
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Setup") // we need this class to get Projectile_BP in C++
	TSubclassOf<AProjectile_C> ProjectileBlueprint; // Alternative { UClass *ProjectileBueprint } and it's get all kind of classess But in our case it get only AProjectile_C or it's derived classess

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000; // TODO find sensible default

	UTankBarrel_C *Barrel = nullptr;
	UTankTurret_C *Turret = nullptr;
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

	FVector AimDirection = FVector(0,0,0); 

	int RoundLeft = 3; // It's used in PlayerUI Widget
	float myDelta = 0; // For DeltaTime Testing

public:

	//==== we deleted this functions because gather them in Initalize() function ====//
	  //void SetTurretReference(UTankTurret_C *);
	  //void SetBarrelReference(UTankBarrel_C *);
};