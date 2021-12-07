// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "KawaiiCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKawaiiCharacterDelegate);

UCLASS()
class BATTLEROYALE_PT_API AKawaiiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKawaiiCharacter();

	virtual void PostInitializeComponents() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Getter functions
	int32 GetStartingHealth();
	int32 GetCurrentHealth();
	int32 GetStartingStamina();
	int32 GetCurrentStamina();

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual bool Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	virtual void OnDeath(float KillingDamage, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser);
	
	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	// Return current stamina as a percentage of starting stamina, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetStaminaPercent() const;

	// TODO remove after testing (for health testing purposes only)
	float TakeDamage2(float DamageAmount);

	void DecreaseHealth();
	void IncreaseHealth(float HealthAmount);

	void DecreaseStamina(float StaminaAmount);
	void IncreaseStamina(float StaminaAmount);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnMeleeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnMeleeEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class AWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* MeleeCollisionComp;

	UFUNCTION(BlueprintCallable, Category = "Collision")
	UCapsuleComponent* GetMeleeCollisionComp() const;

	void SetCanAttack(bool AttackAbility);

	bool GetCanAttack() const;

	bool CanAttack;

	int32 ICanAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack")
	bool IsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attack")
	bool IsBlocking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	bool IsTakingDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	bool IsDancing;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* basicAttackAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* jumpAttackAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* powerAttackAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* basicDamageAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* DeathAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* HealthIncreaseAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	USoundCue* StaminaIncreaseAudioCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* basicAttackAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* jumpAttackAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* powerAttackAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* basicDamageAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* DeathAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* HealthIncreaseAudioComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UAudioComponent* StaminaIncreaseAudioComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for attack */
	void Attack();
	void StopAttacking();

	/** Called for blocking */
	void Block();
	void StopBlocking();

	/** Called for jogging input */
	void Jog();
	void StopJogging();

	/** Called for victory */
	void Victory();

	/* Weapon equipping */
	UFUNCTION()
	void EquipWeapon();

	/* For combat and successful attack detection */
	UFUNCTION()
	void TraceWeapon(float Damage);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialized in BeginPlay

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingStamina = 100;

	UPROPERTY(VisibleAnywhere, Category = "Stamina")
	int32 CurrentStamina; // Initialized in BeginPlay

	/* Handle to manage the damage timer */
	FTimerHandle DamageTimerHandle;

	UFUNCTION()
	void StopTakingDamage();
};
