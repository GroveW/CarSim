// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "CarPawn.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Box"));
	SpawnBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	DestroyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Destroy Box"));
	DestroyBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

	SpawnBox->OnComponentEndOverlap.AddDynamic(this, &AGameManager::OnSpawnEndOverlap);
	DestroyBox->OnComponentBeginOverlap.AddDynamic(this, &AGameManager::OnDestroyBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle EmptyHandle;
	GetWorldTimerManager().SetTimer(EmptyHandle, this, &AGameManager::SpawnCar, FMath::RandRange(MinCarSpawnRate, MaxCarSpawnRate), false);
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::SpawnCar()
{
	if (bSpawnFree)
	{
		FVector SpawnLocation = SpawnBox->GetComponentLocation();
		FRotator SpawnRotation = FVector::RightVector.Rotation() * -45.0f;

		auto SpawnedCar = GetWorld()->SpawnActor(CarPawn, &SpawnLocation, &SpawnRotation);
		auto tmpCarPawn = Cast<ACarPawn>(SpawnedCar);
		tmpCarPawn->SpawnDefaultController();

		float random = FMath::RandRange(0.0f, 29.0f) / 10.0f;
		int randomMatIndex = static_cast<int>(random);

		tmpCarPawn->SetMaterial(CarsMaterials[randomMatIndex]);

		bSpawnFree = false;
	}
}

void AGameManager::OnSpawnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("CarPawn"))
	{
		bSpawnFree = true;
	}

	FTimerHandle EmptyHandle;
	//GetWorldTimerManager().SetTimer(EmptyHandle, this, &AGameManager::SpawnCar, FMath::RandRange(MinCarSpawnRate, MaxCarSpawnRate), false);
}

void AGameManager::OnDestroyBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hitresult)
{
	UE_LOG(LogTemp, Warning, TEXT("begin"));

	if (OtherActor->ActorHasTag("CarPawn"))
	{
		OtherActor->Destroy();
	}
}
