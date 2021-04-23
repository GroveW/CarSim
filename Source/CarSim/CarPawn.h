// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CarPawn.generated.h"

class UFloatingPawnMovement;
class UBoxComponent;

UCLASS()
class CARSIM_API ACarPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACarPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* FloatingPawnMovement;

	float MaxSpeed = 1000.0f;

	UPROPERTY(EditDefaultsOnly)
	float BreakingDistance = 2000.0f;
	UPROPERTY(EditDefaultsOnly)
	float MinimalSafeDistance = 1000.0f;

	UPROPERTY(VisibleAnywhere)
	float DesiredSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere)
	float CurrentSpeed = 0.0f;

	float PreviousDist = 0.0f;

	static int CarCount;

	ACarPawn* ClosestCar = nullptr;

	bool bSafeDistanceReached = false;

	UPROPERTY(EditInstanceOnly)
	bool bStop = false;

	void DriveForward(float DeltaTime);

	void WatchIfCarAhead();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetMaterial(UMaterial* NewMaterial);

	float GetSpeed();
};
