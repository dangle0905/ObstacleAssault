// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

//AActor is the base class
UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	//override specifier specifies that a virtual function overrides another virtual function
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//UPROPERTY SO IT CAN BE VISIBLE to UNREAL
	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	FVector PlatformVelocity = FVector(100,0,0);

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	float MoveDistance = 100;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator RotationVelocity;

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);
	bool ShouldPlatformReturn() const;
	float GetDistanceMoved() const; 

	FVector StartLocation;	



};
