// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPawn.h"

#include "GameFramework/FloatingPawnMovement.h"

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

	DesiredSpeed = FMath::RandRange(0.0f, MaxSped);
}

// Called every frame
void ACarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DriveForward(DeltaTime);
}

// Called to bind functionality to input
void ACarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACarPawn::DriveForward(float DeltaTime)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * DeltaTime * DesiredSpeed);
}

void ACarPawn::WatchIfCarAhead()
{

}

void ACarPawn::SetMaterial(UMaterial* NewMaterial)
{
	Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mesh1")))->SetMaterial(0, NewMaterial);
	Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Mesh2")))->SetMaterial(0, NewMaterial);
}