// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"


// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();

	FString Name = GetName();

	//percent sign is called format specifier %f is floating point number
	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MoveDistance);
	
	//display name of all the actors
	UE_LOG(LogTemp, Display, TEXT("Begin play: %s"), *Name);

	//UE_LOG(LogTemp, Warning, TEXT("Your message"));

	//UE_LOG(LogTemp, Error, TEXT("Your message"));

	

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{


	// send platform back if gone so far
	if (ShouldPlatformReturn())
	{

		//gets the normal from the vector
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		//we get the start location multiplying the normal to the moveDistance (100 at the time) and we do it so we do over shoot and cause drifting
		//so now we have a set start location every time 
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		//we set our platforms start location
		SetActorLocation(StartLocation);
		//direction of velocity is now opposite
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		
	// Move platform forward
		// get the current location
	FVector CurrentLocation = GetActorLocation();
	//when we multiply the velocity by the delta time it makes our frame rate independent (will react on a slow computer and fast computer the same way)
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
	// add vector to that location
	//set the location
	SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("%s is Rotating.."), *GetName());

	//FRotator CurrentRotation = GetActorRotation();
	//CurrentRotation = CurrentRotation + RotationVelocity*DeltaTime;
	// SetActorRotation(CurrentRotation);
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
