// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BasePickUp.generated.h"

UCLASS()
class BATTLEROYALE_PT_API ABasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle DeathTimerHandle;

	void DeathTimerComplete();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PickUpMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationRate;

	float RunningTime;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float XValue;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float YValue;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ZValue = 50;

	UFUNCTION(BlueprintCallable)
	void PlayCustomDeath();

	UFUNCTION(BlueprintNativeEvent)
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
