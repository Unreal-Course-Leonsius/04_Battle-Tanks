// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "TankTurret_C.h"
#include "TankBarrel_C.h"
#include "Projectile_C.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("hokydoky TankAimingComponent Constructor C++ ..."))
	// ...
}



// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("hokydoky TankAimingComponent BeginPlay() C++ ..."))
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel_C *BarrelToSet, UTankTurret_C *TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector OHT, FString ObjN)
{
	auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	if (!Barrel) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Here comes barrel socket location which we created for StartLocation On the barrel

	TArray<AActor*> ActorsToIgnor; // we need it only for debug

	bool SPV = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		OHT,
		LaunchSpeed,
		false,    // we can't missed this and following two parametrs  // false = Not Higharc
		0.f,      // and after that declar ESuggestProjVelocityTraceOption parameter's  // gravity = 0
		0.f,      // and even thouge Ben's code compile that because ::DoNotTrace parameter's appropriate matching Default false paramter's  // radiuse = 0
		ESuggestProjVelocityTraceOption::DoNotTrace
		//FCollisionResponseParams::DefaultResponseParam,
		//ActorsToIgnor,
		//true
	);


	if(SPV)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); // We need not Unit Vector we can directly convert FVector to FRotator: { FRotator OutLaunchVelocityRotator = OutLaunchVelocity.Rotation(); }
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f Aiming"),Time);
		//UE_LOG(LogTemp, Error, TEXT("%f DeltaTime"), GetWorld()->DeltaTimeSeconds);
		MoveBarrel(AimDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f Not Aiming"), Time);
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("LaunchSpeed %f"), LaunchSpeed);  // %f means float
		
}

void UTankAimingComponent::MoveBarrel(FVector &AimDirection)
{
	// Work-out difference between cuurent barrel rotation and AimDirection
	if (!Barrel) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimsRotator = AimDirection.Rotation();

	//UE_LOG(LogTemp, Warning, TEXT("BarrelForwardVector = %s, BarrelForwarRotation = %s"),*Barrel->GetForwardVector().ToString(), *BarrelRotator.ToString())

	auto DeltaRotator = AimsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	/*UE_LOG(LogTemp, Warning, TEXT("%s TurretPostion: %f"), *GetOwner()->GetName(), Turret->RelativeRotation.Yaw);
	UE_LOG(LogTemp, Warning, TEXT("%s AimsRotator: %f"), *GetOwner()->GetName(), AimsRotator.Yaw);
	UE_LOG(LogTemp, Warning, TEXT("%s DeltaRotator: %f"), *GetOwner()->GetName(), DeltaRotator.Yaw);

	if (ObjN == "Tank_BP2_3312")
	{
		UE_LOG(LogTemp, Error, TEXT("%s AimsRotator: %s"), *GetOwner()->GetName(), *AimsRotator.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s AimsRotator: %s"), *GetOwner()->GetName(), *AimsRotator.ToString());
	}

	UE_LOG(LogTemp, Warning, TEXT("%s TurretPostion: %s"), *GetOwner()->GetName(), *BarrelRotator.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s AimsRotator: %s"), *GetOwner()->GetName(), *AimsRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s DeltaRotator: %s"), *GetOwner()->GetName(), *DeltaRotator.ToString());

	Turret->Rotate(DeltaRotator.Yaw); */
	
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw);
	}

}


void UTankAimingComponent::Firing()
{
	//UE_LOG(LogTemp, Warning, TEXT("ProjectileBP... %s"), *ProjectileBlueprint->GetName());

	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	bool IsReload = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (IsReload)
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

}


/*void UTankAimingComponent::SetBarrelReference(UTankBarrel_C *BarrelToSet)
{
Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(UTankTurret_C *TurretToSet)
{
Turret = TurretToSet;
}*/


