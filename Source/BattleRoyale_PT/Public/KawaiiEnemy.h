// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KawaiiCharacter.h"
#include "Weapon.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "KawaiiEnemy.generated.h"

UCLASS()
class BATTLEROYALE_PT_API AKawaiiEnemy : public AKawaiiCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKawaiiEnemy();

	UPROPERTY(VisibleAnywhere, Category = "Skeletal Mesh")
	USkeletalMesh* MeshContainer;

	/* The component which is used for the "seeing" sense of the AI */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	/* The behavior tree of the character */
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	/* Last time the player was spotted */
	float LastSeenTime;

	/* Last time the player was heard */
	float LastHeardTime;

	/* Last time we attached something */
	float LastMeleeAttackTime;

	/* Time-out value to clear the sensed position of the player
	should be higher than Sense interval in the PawnSense component
	not never miss sense ticks. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SenseTimeOut;

	/* Resets after sense time-out to avoid unnecessary clearing of target each tick */
	bool bSensedTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RandomizeAppearance();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

	/* A pawn is in melee range */
	//UFUNCTION()
	//void OnMeleCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
