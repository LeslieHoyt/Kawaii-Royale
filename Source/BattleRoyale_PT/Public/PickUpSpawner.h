// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.h"
#include "PickUpSpawner.generated.h"

UCLASS()
class BATTLEROYALE_PT_API APickUpSpawner : public ABaseSpawner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Spawn(int32 SpawnLimit) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
