// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class ACarPawn;
class UMaterial;

UCLASS()
class CARSIM_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnBox;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* DestroyBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACarPawn> CarPawn;

	UPROPERTY(EditDefaultsOnly)
	float MinCarSpawnRate = 2.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxCarSpawnRate = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterial*> CarsMaterials;

	bool bSpawnFree = true;

	void SpawnCar();

	UFUNCTION()
	void OnSpawnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnDestroyBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hitresult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
