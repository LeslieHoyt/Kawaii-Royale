// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"

UCLASS()
class BATTLEROYALE_PT_API ABaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Spawn(int32 SpawnLimit); // child classes must override this

	void GenerateSpawnPoints(int32 spawnLimit, int32 xLim, int32 yLim, int32 zLim);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	float SpawnPoint;

	float TimeSinceLastSpawn;

};
