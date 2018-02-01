// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
//#include "TankAimingComponent.h"
//#include "Projectile_C.h"
//#include "TankBarrel_C.h"
#include "Tank_C.h"


// Sets default values
ATank_C::ATank_C()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // may be it false we need not it

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("OkyDoky Tank C++ Constractor %s..."), *TankName);
	// No need to protect points as added at construction

	/// if I here created AimingComponent it would be inherited in BP and we don't want thus.
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName ("Aiming Component"));  

	/// TankAimingComponent = nullptr because Tank_C Constructor Runs befor Tank_BP therefor FindComponentByClass() can't finde AimingComponent
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

}

// Called when the game starts or when spawned
void ATank_C::BeginPlay()
{
	// we don't use this but its nessesary for Tank_BP. it's beginPlay() couldn't work without this code (Super::BeginPlaye(); virtual Function)
	// OR we can delete BeginPlay() at all
	Super::BeginPlay();

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("OkyDoky Tank C++ BeginPlaye %s..."), *TankName);

	/// IN here gets Tank_BP AimingComponent
	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>(); 
	//UE_LOG(LogTemp, Warning, TEXT("TankAimingComponent name ... %s"), *TankAimingComponent->GetName())

	/// CreateDefaultSubobjcet() is a Constructor function isn't working in BegingPlay() 
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called every frame
void ATank_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank_C::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


//=============================== WE NEED NOT THIS FUNCTION ANY MORE ==========================///
//=========================== We Delete some of this and Remove others ======================///


/// Remove To TankAimingComponent
/*void ATank_C::AimAt(FVector HitLocation, FString ObjecName)
{
	if (!ensure(TankAimingComponent)){ return; }
	
	TankAimingComponent->AimAt(HitLocation, ObjecName, LaunchSpeed);
	UE_LOG(LogTemp, Warning, TEXT("I am here"));
	//UTankAimingComponent::AimAt(HitLocation, ObjecName); // it's not work because UTankAimingComponent is not it's parent class without inheritnace it wouldn't be call function like this
}*/

/// Deleted
/*void ATank_C::SetTurretReference(UTankTurret_C * TurretToSet)
{
	if (!TurretToSet || !TankAimingComponent) { return; }
	TankAimingComponent->SetTurretReference(TurretToSet);
}



void ATank_C::SetBarrelReference(UTankBarrel_C * BarrelToSet)
{
	if (!BarrelToSet || !TankAimingComponent) { return; }
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}*/

/// Remove
/*void ATank_C::Firing()
{
	//UE_LOG(LogTemp, Warning, TEXT("ProjectileBP... %s"), *ProjectileBlueprint->GetName());

	bool IsReload = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && IsReload)
	{
		// Spawn a projectile at the socket location on the barrel
			 // Projectile = AProjectile_C it's Actor of Spawning
		auto Projectile = GetWorld()->SpawnActor<AProjectile_C>(
			ProjectileBlueprint, // Spawn
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))  // it's matching Projectile's ForwardVector
			);

		     //AProjectile_C *APC = Projectile;
	        //FString Name = APC->GetName();
        //UE_LOG(LogTemp, Warning, TEXT("Projectile.. %s"), *Projectile->GetName());
		
		//UE_LOG(LogTemp,Warning,TEXT("TankName = %s"),*Controller->GetName())

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

	}

}*/

	        



