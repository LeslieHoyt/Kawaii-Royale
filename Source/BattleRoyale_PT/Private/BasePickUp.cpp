// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickUp.h"
#include "KawaiiPlayerCharacter.h"
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"

// Sets default values
ABasePickUp::ABasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickUpMesh");
	PickUpMesh->SetupAttachment(Root);
	PickUpMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RotationRate = 100;

	OnActorBeginOverlap.AddDynamic(this, &ABasePickUp::OnOverlap);
}

// Called when the game starts or when spawned
void ABasePickUp::BeginPlay()
{
	Super::BeginPlay();

	// Set starting height
	FVector NewLocation = GetActorLocation();
	NewLocation.Z = 190;
	SetActorLocation(NewLocation);
	
}

// Called every frame
void ABasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));

	// on every frame change location for a smooth floating actor
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.X += DeltaHeight * XValue;
	NewLocation.Y += DeltaHeight * YValue;
	NewLocation.Z += DeltaHeight * ZValue;
	if (NewLocation.Z < 0)
	{
		NewLocation.Z = 0;
	}

	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}

void ABasePickUp::DeathTimerComplete()
{
	Destroy();
}

void ABasePickUp::PlayCustomDeath()
{
	RotationRate = 1500;
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ABasePickUp::DeathTimerComplete, 0.5f, false);
}

void ABasePickUp::OnOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<AKawaiiPlayerCharacter>(OtherActor) != nullptr)
	{
		Destroy();
	}
}

