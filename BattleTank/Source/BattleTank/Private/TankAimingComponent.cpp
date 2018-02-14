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
	//bWantsBeginPlay = true; // it was not here and I put it myself and then UE editor fix Error this line
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}



// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// So that it happance first and after initial reload and AITank don't fire from scratch
	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Ben dont add Super::
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*myDelta = myDelta + DeltaTime;
	UE_LOG(LogTemp, Warning, TEXT("myDelta %f"), myDelta);
	RoundLeft = RoundLeft - int(myDelta);  //  DeltaTime is not working here
	RoundLeft = 1+ReloadTimeInSeconds + LastFireTime - FPlatformTime::Seconds(); // whereas such way it works
	*/
	// ...
	if (RoundLeft <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (!IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	//FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile")); // AimDirection is unit Vector therefor useless GetSocketLocatrion and need GetForwardVector()
	FVector StartLocation = Barrel->GetForwardVector();
	
	return StartLocation.Equals(AimDirection,0.01);
}

void UTankAimingComponent::Initialize(UTankBarrel_C *BarrelToSet, UTankTurret_C *TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector OHT, FString ObjN)
{
	
	//auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	if (!Barrel) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Here comes barrel socket location which we created for StartLocation On the barrel
	//FVector StartLocation = Barrel->GetForwardVector() // GetForwardVector() is not working in SuggestProjectileVelocity function, because SuggestProjectileVelocity need point which calculate from Global axis
	//FVector StartLocation = Barrel->GetComponentLocation(); // we can use it instead of Barrel->GetSocketLocation(FName("Projectile"));


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
		AimDirection = OutLaunchVelocity.GetSafeNormal(); // We need not Unit Vector we can directly convert FVector to FRotator: { FRotator OutLaunchVelocityRotator = OutLaunchVelocity.Rotation(); }
		auto Time = GetWorld()->GetTimeSeconds();
		MoveBarrel();
	}
	else
	{
		// TODO why it is not working
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f Not Aiming"), Time);
	}

	/// it nessescary only to check Barrel, Socket, AimDirection Location.
	// TODO Socket Location is not matching AimDirection Location ????? 
	// BECAUSE SocketLocation is calculated from Global Location and SocketLocation().GetSafeNormal(); aslo from Global Location
	/*auto TankName = GetOwner()->GetName();
	if (TankName == "Tank_BP_C_0")
	{
		UE_LOG(LogTemp, Warning, TEXT("AimDirection %s"), *AimDirection.ToString());
		StartLocation = StartLocation.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("StartLocation %s"), *StartLocation.ToString());
		auto BarrelLocation = Barrel->GetForwardVector();
		UE_LOG(LogTemp, Warning, TEXT("BarrelLocation %s"), *BarrelLocation.ToString());
	}
	*/
	
	//UE_LOG(LogTemp, Warning, TEXT("LaunchSpeed %f"), LaunchSpeed);  // %f means float
		
}

void UTankAimingComponent::MoveBarrel()
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

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}


void UTankAimingComponent::Firing()
{
	//UE_LOG(LogTemp, Warning, TEXT("ProjectileBP... %s"), *ProjectileBlueprint->GetName());

	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		// Spawn a projectile at the socket location on the barrel
		// Projectile = AProjectile_C it's Actor of Spawning
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
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
		//FiringState = EFiringState::Reloading;
		RoundLeft--;

	}

}

int32 UTankAimingComponent::GetRoundLeft() const
{
	return RoundLeft;
}


/*void UTankAimingComponent::SetBarrelReference(UTankBarrel_C *BarrelToSet)
{
Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(UTankTurret_C *TurretToSet)
{
Turret = TurretToSet;
}*/


