// Fill out your copyright notice in the Description page of Project Settings.

#include "KawaiiCharacter.h"
#include "BattleRoyale_PT.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Weapon.h"

// Sets default values
AKawaiiCharacter::AKawaiiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/// Basic Attack SFX
	// Load sound cue for basic attack sound
	static ConstructorHelpers::FObjectFinder<USoundCue> basicAttackCue(TEXT("'/Game/Audio/SFX/BasicAttack_SoundCue.BasicAttack_SoundCue'"));
	// Store a reference to the cue asset
	basicAttackAudioCue = basicAttackCue.Object;
	// Create an audio component, the audio component wraps the cue, and allows us to interact
	// with it and its parameters from code
	basicAttackAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BasicAttackAudioComp"));
	basicAttackAudioComponent->bAutoActivate = false; // don't play the sound immediately
	basicAttackAudioComponent->AutoAttachParent = RootComponent; // follows the character

	/// Jump Attack SFX
	// Load sound cue for basic attack sound
	static ConstructorHelpers::FObjectFinder<USoundCue> jumpAttackCue(TEXT("'/Game/Audio/SFX/JumpAttack_SoundCue.JumpAttack_SoundCue'"));
	// Store a reference to the cue asset
	jumpAttackAudioCue = jumpAttackCue.Object;
	// Create an audio component, the audio component wraps the cue, and allows us to interact
	// with it and its parameters from code
	jumpAttackAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("JumpAttackAudioComp"));
	jumpAttackAudioComponent->bAutoActivate = false; // don't play the sound immediately
	jumpAttackAudioComponent->AutoAttachParent = RootComponent; // follows the character

	/// Power Attack SFX
	// Load sound cue for basic attack sound
	static ConstructorHelpers::FObjectFinder<USoundCue> powerAttackCue(TEXT("'/Game/Audio/SFX/PowerAttack_SoundCue.PowerAttack_SoundCue'"));
	// Store a reference to the cue asset
	powerAttackAudioCue = powerAttackCue.Object;
	// Create an audio component, the audio component wraps the cue, and allows us to interact
	// with it and its parameters from code
	powerAttackAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PowerAttackAudioComp"));
	powerAttackAudioComponent->bAutoActivate = false; // don't play the sound immediately
	powerAttackAudioComponent->AutoAttachParent = RootComponent; // follows the character

	/// Basic Damage SFX
	// Load sound cue for basic damage sound
	static ConstructorHelpers::FObjectFinder<USoundCue> basicDamageCue(TEXT("'/Game/Audio/SFX/BasicDamage_SoundCue.BasicDamage_SoundCue'"));
	// Store a reference to the cue asset
	basicDamageAudioCue = basicDamageCue.Object;
	// Create an audio component, the audio component wraps the cue, and allows us to interact
	// with it and its parameters from code
	basicDamageAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BasicDamageAudioComp"));
	basicDamageAudioComponent->bAutoActivate = false; // don't play the sound immediately
	basicDamageAudioComponent->AutoAttachParent = RootComponent; // follows the character

	/// Death SFX
	// Load sound cue for death sound
	static ConstructorHelpers::FObjectFinder<USoundCue> DeathCue(TEXT("'/Game/Audio/SFX/Death_SoundCue.Death_SoundCue'"));
	// Store a reference to the cue asset
	DeathAudioCue = DeathCue.Object;
	// Create an audio component, the audio component wraps the cue, and allows us to interact
	// with it and its parameters from code
	DeathAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DeathAudioComp"));
	DeathAudioComponent->bAutoActivate = false; // don't play the sound immediately
	DeathAudioComponent->AutoAttachParent = RootComponent; // follows the character

	/// Health Increase SFX
	// Load sound cue for death sound
	static ConstructorHelpers::FObjectFinder<USoundCue> HealthCue(TEXT("'/Game/Audio/SFX/HealthIncrease_SoundCue.HealthIncrease_SoundCue'"));
	// Store a reference to the cue asset
	HealthIncreaseAudioCue = HealthCue.Object;
	// Create an audio component, the audio component wraps the cue, and allows us to interact
	// with it and its parameters from code
	HealthIncreaseAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HealthIncreaseAudioComp"));
	HealthIncreaseAudioComponent->bAutoActivate = false; // don't play the sound immediately
	HealthIncreaseAudioComponent->AutoAttachParent = RootComponent; // follows the character

	/// Stamina Increase SFX
	// Load sound cue for death sound
	static ConstructorHelpers::FObjectFinder<USoundCue> StaminaCue(TEXT("'/Game/Audio/SFX/StaminaIncrease_SoundCue.StaminaIncrease_SoundCue'"));
	// Store a reference to the cue asset
	StaminaIncreaseAudioCue = StaminaCue.Object;
	// Create an audio component, the audio component wraps the cue, and allows us to interact
	// with it and its parameters from code
	StaminaIncreaseAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("StaminaIncreaseAudioComp"));
	StaminaIncreaseAudioComponent->bAutoActivate = false; // don't play the sound immediately
	StaminaIncreaseAudioComponent->AutoAttachParent = RootComponent; // follows the character

	/// Collision Setup
	MeleeCollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeCollision"));
	MeleeCollisionComp->SetCapsuleHalfHeight(89);
	MeleeCollisionComp->SetCapsuleRadius(46, false);
	MeleeCollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeCollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeleeCollisionComp->SetupAttachment(GetCapsuleComponent());
	MeleeCollisionComp->bDynamicObstacle = true;
	MeleeCollisionComp->SetGenerateOverlapEvents(true);

	GetMeleeCollisionComp()->OnComponentHit.AddDynamic(this, &AKawaiiCharacter::OnHit);
	GetMeleeCollisionComp()->OnComponentBeginOverlap.AddDynamic(this, &AKawaiiCharacter::OnMeleeBeginOverlap);
	GetMeleeCollisionComp()->OnComponentEndOverlap.AddDynamic(this, &AKawaiiCharacter::OnMeleeEndOverlap);
}

void AKawaiiCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (basicAttackAudioCue->IsValidLowLevelFast())
	{
		basicAttackAudioComponent->SetSound(basicAttackAudioCue);
	}
	if (jumpAttackAudioCue->IsValidLowLevelFast())
	{
		jumpAttackAudioComponent->SetSound(jumpAttackAudioCue);
	}
	if (powerAttackAudioCue->IsValidLowLevelFast())
	{
		powerAttackAudioComponent->SetSound(powerAttackAudioCue);
	}
	if (basicDamageAudioCue->IsValidLowLevelFast())
	{
		basicDamageAudioComponent->SetSound(basicDamageAudioCue);
	}
	if (DeathAudioCue->IsValidLowLevelFast())
	{
		DeathAudioComponent->SetSound(DeathAudioCue);
	}
	if (HealthIncreaseAudioCue->IsValidLowLevelFast())
	{
		HealthIncreaseAudioComponent->SetSound(HealthIncreaseAudioCue);
	}
	if (StaminaIncreaseAudioCue->IsValidLowLevelFast())
	{
		StaminaIncreaseAudioComponent->SetSound(StaminaIncreaseAudioCue);
	}
}

// Called when the game starts or when spawned
void AKawaiiCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
	CurrentStamina = StartingStamina;
	EquipWeapon();
}

void AKawaiiCharacter::EquipWeapon()
{
	FActorSpawnParameters SpawnParams;
	AWeapon* Spawner = GetWorld()->SpawnActor<AWeapon>(this->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
	if (Spawner)
	{
		Weapon = Spawner;
		Weapon->SetOwningPawn(this);
		Weapon->AttachMeshToPawn(this);
		//Weapon->GetCollisionMesh()->OnComponentHit.AddDynamic(this, &AKawaiiCharacter::OnHit);
		//Weapon->GetCollisionMesh()->OnComponentBeginOverlap.AddDynamic(this, &AKawaiiCharacter::OnMeleeBeginOverlap);
	}
}

void AKawaiiCharacter::TraceWeapon(float Damage)
{
	if (Weapon == nullptr)
	{
		return;
	}
	UStaticMeshComponent* WeapMesh = Weapon->GetWeaponMesh();
	FVector TraceStart = Weapon->GetActorForwardVector();
	FVector TraceEnd = ((TraceStart * 5) + Weapon->GetActorLocation());
	ECollisionChannel CollisionChannel = ECC_Pawn;
	FCollisionQueryParams TraceParams(FName(TEXT("WeaponTrace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActor(this);
	FHitResult HitData(ForceInit);
	if (GetWorld()->LineTraceSingleByChannel(HitData, TraceStart, TraceEnd, CollisionChannel, TraceParams))
	{
		if (HitData.Actor->IsA<AKawaiiCharacter>())
		{
			FPointDamageEvent DmgEvent;
			HitData.Actor->TakeDamage(Damage, DmgEvent, GetController(), this);
			UE_LOG(LogTemp, Warning, TEXT("This seems to work"));
		}
	}
}

void AKawaiiCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComponent != NULL))
	{
		AKawaiiCharacter* OtherChara = Cast<AKawaiiCharacter>(OtherActor);
		if (this->CanAttack == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack!"));
		}
	}
}

void AKawaiiCharacter::OnMeleeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		AKawaiiCharacter* OtherChara = Cast<AKawaiiCharacter>(OtherActor);
		OtherChara->CanAttack = true;
		if (OtherChara->CanAttack == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("Can attack now"));
		}
	}
}

void AKawaiiCharacter::SetCanAttack(bool AttackAbility)
{
	CanAttack = AttackAbility;
}

bool AKawaiiCharacter::GetCanAttack() const
{
	return CanAttack;
}

void AKawaiiCharacter::OnMeleeEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		AKawaiiCharacter* OtherChara = Cast<AKawaiiCharacter>(OtherActor);
		// to get jump attack to work, let's try not setting
		// this to false until confirm character is on the ground
		OtherChara->CanAttack = false;
		UE_LOG(LogTemp, Warning, TEXT("Cannot attack now"));
	}
}

UCapsuleComponent* AKawaiiCharacter::GetMeleeCollisionComp() const
{
	return MeleeCollisionComp;
}

void AKawaiiCharacter::Attack()
{
	IsAttacking = true;
	if (this->CanAttack == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack happened"));
		// Check if player is running
		if (GetCharacterMovement()->MaxWalkSpeed > 200.f)
		{
			// Power attack
			powerAttackAudioComponent->Play();
			DecreaseStamina(10);
			TraceWeapon(20);
		}
		else if (GetCharacterMovement()->IsFalling())
		{
			// Jump attack
			jumpAttackAudioComponent->Play();
			DecreaseStamina(10);
			TraceWeapon(20);
		}
		else
		{
			// Player is either idle or walking
			// Basic attack
			basicAttackAudioComponent->Play();
			TraceWeapon(10);
		}
	}
}

void AKawaiiCharacter::StopAttacking()
{
	IsAttacking = false;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void AKawaiiCharacter::Block()
{
	IsBlocking = true;
}

void AKawaiiCharacter::StopBlocking()
{
	IsBlocking = false;
}

void AKawaiiCharacter::Jog()
{
	GetCharacterMovement()->MaxWalkSpeed = 375.f;
}

void AKawaiiCharacter::StopJogging()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}

void AKawaiiCharacter::Victory()
{
	IsDancing = true;
}

float AKawaiiCharacter::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

float AKawaiiCharacter::GetStaminaPercent() const
{
	return (float)CurrentStamina / (float)StartingStamina;
}

int32 AKawaiiCharacter::GetStartingHealth()
{
	return StartingHealth;
}

int32 AKawaiiCharacter::GetCurrentHealth()
{
	return CurrentHealth;
}

int32 AKawaiiCharacter::GetStartingStamina()
{
	return StartingStamina;
}

int32 AKawaiiCharacter::GetCurrentStamina()
{
	return CurrentStamina;
}

float AKawaiiCharacter::TakeDamage2(float DamageAmount)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	// check if blocking
	if (!IsBlocking)
	{
		CurrentHealth -= DamageToApply;
		if (DamageToApply == 10)
		{
			// basic damage
			basicDamageAudioComponent->Play();
		}
		if (CurrentHealth <= 0)
		{
			//OnDeath.Broadcast();
			DeathAudioComponent->Play();
		}
	}
	else 
	{
		// blocking negates all damage
		DamageToApply = 0;
	}
	return DamageToApply;
}

float AKawaiiCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	// check if blocking
	if (!IsBlocking)
	{
		CurrentHealth -= DamageToApply;
		if (CurrentHealth <= 0)
		{
			//OnDeath.Broadcast();
			DeathAudioComponent->Play();
			Die(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			IsTakingDamage = true;
			Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
			basicDamageAudioComponent->Play();
			if (IsTakingDamage)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Hey! Executing here"));
				float MaxDamageTime = 0.5f;
				if (GetWorld() != NULL)
				{
					GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle,
						this,
						&AKawaiiCharacter::StopTakingDamage,
						MaxDamageTime,
						false);
				}
			}
		}
	}
	else
	{
		// blocking negates all damage
		DamageToApply = 0;
	}
	return DamageToApply;
}

bool AKawaiiCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	OnDeath(KillingDamage, DamageEvent, Killer ? Killer->GetPawn() : NULL, DamageCauser);
	return true;
}

void AKawaiiCharacter::OnDeath(float KillingDamage, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	IsDead = true;

	/* Disable all collision on capsule */
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);
}

void AKawaiiCharacter::DecreaseHealth()
{
	TakeDamage2(10);
	// Note: basic attacks will deal 10 damage
	// Power attacks will deal 20 damage
	if (GetHealthPercent() == 0)
	{
		IsDead = true;
	}
	else {
		IsTakingDamage = true;
		if (IsTakingDamage)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Hey! Executing here"));
			float MaxDamageTime = 0.5f;
			if (GetWorld() != NULL)
			{
				GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle,
					this,
					&AKawaiiCharacter::StopTakingDamage,
					MaxDamageTime,
					false);
			}
		}
	}
}

void AKawaiiCharacter::IncreaseHealth(float HealthAmount)
{
	if (CurrentHealth < StartingHealth)
	{
		int32 HealthPoints = FPlatformMath::RoundToInt(HealthAmount);
		int32 HealthToApply = FMath::Clamp(HealthPoints, 0, CurrentHealth);

		// increase health
		CurrentHealth += HealthToApply;
		HealthIncreaseAudioComponent->Play();
	}
}

void AKawaiiCharacter::DecreaseStamina(float StaminaAmount)
{
	int32 StaminaPoints = FPlatformMath::RoundToInt(StaminaAmount);
	int32 StaminaToApply = FMath::Clamp(StaminaPoints, 0, CurrentStamina);

	CurrentStamina -= StaminaToApply;
}

void AKawaiiCharacter::IncreaseStamina(float StaminaAmount)
{
	if (CurrentStamina < StartingStamina)
	{
		int32 StaminaPoints = FPlatformMath::RoundToInt(StaminaAmount);
		int32 StaminaToApply = FMath::Clamp(StaminaPoints, 0, CurrentStamina);

		// increase stamina
		CurrentStamina += StaminaToApply;
		StaminaIncreaseAudioComponent->Play();
	}
}

void AKawaiiCharacter::StopTakingDamage()
{
	IsTakingDamage = false;
	// Ensure the damage timer is cleared by using the timer handle
	if (GetWorld() != NULL)
	{
		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	}
}

// Called every frame
void AKawaiiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKawaiiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

