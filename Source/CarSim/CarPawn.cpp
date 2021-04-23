// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPawn.h"

#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

int ACarPawn::CarCount = 0;

// Sets default values
ACarPawn::ACarPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));
}

// Called when the game starts or when spawned
void ACarPawn::BeginPlay()
{
	Super::BeginPlay();

	CarCount++;

	if (CarCount % 5 == 0)
		DesiredSpeed = 50.0f;
	else
		DesiredSpeed = FMath::RandRange(50.0f, MaxSpeed);

	CurrentSpeed = DesiredSpeed;
}

// Called every frame
void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DriveForward(DeltaTime);
	WatchIfCarAhead();
}

// Called to bind functionality to input
void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACarPawn::DriveForward(float DeltaTime)
{
	if (bStop)
		return;

	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * DeltaTime * CurrentSpeed);
}

void ACarPawn::WatchIfCarAhead()
{
	if (!ClosestCar)
	{
		CurrentSpeed = DesiredSpeed;

		FVector StartPos = GetActorLocation();
		FHitResult HitResult;

		if (GetWorld()->LineTraceSingleByObjectType(HitResult, StartPos, StartPos + GetActorForwardVector() * BreakingDistance,
			FCollisionObjectQueryParams::AllDynamicObjects))
		{
			if (HitResult.Actor->ActorHasTag("CarPawn"))
			{
				ClosestCar = Cast<ACarPawn>(HitResult.Actor);
			}
		}
	}
	else if (ClosestCar && ClosestCar->IsActorBeingDestroyed())
	{
		UE_LOG(LogTemp, Warning, TEXT("DESTROYED"));

		ClosestCar = nullptr;
		CurrentSpeed = DesiredSpeed;
	}
	else
	{
		CurrentSpeed = ClosestCar->GetSpeed();

		float CurrentDist = FVector::Distance(ClosestCar->GetActorLocation(), GetActorLocation());

		if (CurrentSpeed > DesiredSpeed || CurrentDist > BreakingDistance)
		{
			ClosestCar = nullptr;
			CurrentSpeed = DesiredSpeed;
		}
	}
}

void ACarPawn::SetMaterial(UMaterial* NewMaterial)
{
	Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mesh1")))->SetMaterial(0, NewMaterial);
	Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mesh2")))->SetMaterial(0, NewMaterial);
}

float ACarPawn::GetSpeed()
{
	if (bStop)
		return 0.0f;

	return CurrentSpeed;
}