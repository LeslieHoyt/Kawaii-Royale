// Fill out your copyright notice in the Description page of Project Settings.


#include "StarPickUp.h"
#include "BasePickUp.h"
#include "KawaiiPlayerCharacter.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"

// Sets default values
AStarPickUp::AStarPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// star mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("'/Game/Items/PickUps/SM_StarPickUp.SM_StarPickUp'"));
	UStaticMesh* Asset = MeshAsset.Object;
	PickUpMesh->SetStaticMesh(Asset);

	// explosion
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("'/Game/FX/PS_GreenStar_Stamina.PS_GreenStar_Stamina'"));
	ExplosionFX = Particle.Object;

}

// Called when the game starts or when spawned
void AStarPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStarPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStarPickUp::DeathTimerComplete()
{
	Destroy();
}

void AStarPickUp::OnOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((Cast<AKawaiiPlayerCharacter>(OtherActor) != nullptr) &&
		(Cast<AKawaiiPlayerCharacter>(OtherActor)->GetCurrentStamina() < Cast<AKawaiiPlayerCharacter>(OtherActor)->GetStartingStamina()))
	{
		RotationRate = 1500;
		// Restore stamina
		Cast<AKawaiiPlayerCharacter>(OtherActor)->IncreaseStamina(10);
		if (ExplosionFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFX, GetActorLocation());
		}
		GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AStarPickUp::DeathTimerComplete, 0.5f, false);
	}
}

