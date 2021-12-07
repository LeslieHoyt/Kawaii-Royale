// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "KawaiiCharacter.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Weapon.generated.h"

UCLASS()
class BATTLEROYALE_PT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CollisionMesh;

	UFUNCTION(BlueprintCallable, Category = "Collision")
	UBoxComponent* GetCollisionMesh() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UStaticMeshComponent* GetWeaponMesh() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	AKawaiiCharacter* GetPawnOwner() const;

	/* Set the weapon's owning pawn */
	void SetOwningPawn(AKawaiiCharacter* Owner);

	void AttachMeshToPawn(AKawaiiCharacter* Pawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* pawn owner */
	UPROPERTY(VisibleAnywhere)
	AKawaiiCharacter* MyPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
