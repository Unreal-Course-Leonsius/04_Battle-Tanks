// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel_C.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel_C *BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector OHT, FString ObjN, float LaunchSpeed)
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

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimsRotator = AimDirection.Rotation();

	auto DeltaRotator = AimsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

}


