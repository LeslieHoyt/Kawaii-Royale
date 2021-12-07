// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.h"
#include "StarPickUp.generated.h"

UCLASS()
class BATTLEROYALE_PT_API AStarPickUp : public ABasePickUp
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStarPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FX")
	UParticleSystem* ExplosionFX;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DeathTimerComplete();

	void OnOverlap_Implementation(AActor * OverlappedActor, AActor * OtherActor);

};
