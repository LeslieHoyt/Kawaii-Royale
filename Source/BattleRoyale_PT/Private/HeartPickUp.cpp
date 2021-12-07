// Fill out your copyright notice in the Description page of Project Settings.


#include "HeartPickUp.h"
#include "BasePickUp.h"
#include "KawaiiPlayerCharacter.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"

// Sets default values
AHeartPickUp::AHeartPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// heart mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("'/Game/Items/PickUps/SM_HeartPickUp.SM_HeartPickUp'"));
	UStaticMesh* Asset = MeshAsset.Object;
	PickUpMesh->SetStaticMesh(Asset);

	// explosion
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("'/Game/FX/PS_RedHeart_Health.PS_RedHeart_Health'"));
	ExplosionFX = Particle.Object;

}

// Called when the game starts or when spawned
void AHeartPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHeartPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeartPickUp::DeathTimerComplete()
{
	Destroy();
}

void AHeartPickUp::OnOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((Cast<AKawaiiPlayerCharacter>(OtherActor) != nullptr) && 
		(Cast<AKawaiiPlayerCharacter>(OtherActor)->GetCurrentHealth() < Cast<AKawaiiPlayerCharacter>(OtherActor)->GetStartingHealth()))
	{
		RotationRate = 1500;
		// Restore health
		Cast<AKawaiiPlayerCharacter>(OtherActor)->IncreaseHealth(10);
		if (ExplosionFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFX, GetActorLocation());
		}
		GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AHeartPickUp::DeathTimerComplete, 0.5f, false);
	}
}

