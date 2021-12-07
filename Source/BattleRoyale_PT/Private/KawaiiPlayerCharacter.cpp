// Fill out your copyright notice in the Description page of Project Settings.

#define ECC_Player ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Enemy ECollisionChannel::ECC_GameTraceChannel2
#include "KawaiiPlayerCharacter.h"
#include "BattleRoyale_PT.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapon.h"

// Sets default values
AKawaiiPlayerCharacter::AKawaiiPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-30.f, 90.f, 0.f));
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	// set collision type for this character
	GetMeleeCollisionComp()->SetCollisionObjectType(ECC_Player);
	if (GetMeleeCollisionComp()->GetCollisionObjectType() == ECC_Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player set correctly"));
	}
}

// Called when the game starts or when spawned
void AKawaiiPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set weapon collision
	Weapon->GetCollisionMesh()->SetCollisionObjectType(ECC_Player);
	Weapon->GetCollisionMesh()->SetCollisionResponseToChannel(ECC_Player, ECR_Ignore);
	GetMeleeCollisionComp()->SetCollisionResponseToChannel(ECC_Player, ECR_Ignore);
	//Weapon->GetWeaponMesh()->MoveIgnoreActors.Add(this);
	//Weapon->GetWeaponMesh()->MoveIgnoreActors.Add(Weapon);
	//GetMesh()->MoveIgnoreActors.Add(Weapon);
	Weapon->GetCollisionMesh()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Overlap);
	GetMeleeCollisionComp()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMeleeCollisionComp()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Block);
	
}

void AKawaiiPlayerCharacter::MoveForward(float Value)
{
	// Find out which way is forward
	FRotator Rotation = Controller->GetControlRotation();
	// Limit pitch when walking or falling
	if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
	{
		Rotation.Pitch = 0.0f;
	}
	// Add movement in that direction
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AKawaiiPlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		// Add Movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AKawaiiPlayerCharacter::Jump()
{
	if (GetCharacterMovement()->MaxWalkSpeed > 160.f)
	{
		Super::Jump();
		GetCharacterMovement()->JumpZVelocity = 365.f;
	}
}

void AKawaiiPlayerCharacter::TurnAtRate(float Rate)
{
	// Find out which way to turn
	const FRotator Rotation = Controller->GetControlRotation();
	FRotator NewRotation;
	NewRotation.Roll = 0.f;
	NewRotation.Pitch = 0.f;
	NewRotation.Yaw = Rotation.Yaw;
	// Rotate character in that direction
	//SetActorRelativeRotation(NewRotation, Rate);
}

// Called every frame
void AKawaiiPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKawaiiPlayerCharacter::LookUpAtRate(float Rate)
{
}

// Called to bind functionality to input
void AKawaiiPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKawaiiPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AKawaiiPlayerCharacter::StopJumping);

	PlayerInputComponent->BindAction("Jog", IE_Pressed, this, &AKawaiiPlayerCharacter::Jog);
	PlayerInputComponent->BindAction("Jog", IE_Released, this, &AKawaiiPlayerCharacter::StopJogging);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKawaiiPlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AKawaiiPlayerCharacter::StopAttacking);

	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AKawaiiPlayerCharacter::Block);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &AKawaiiPlayerCharacter::StopBlocking);

	// TODO remove, just for testing
	PlayerInputComponent->BindAction("Victory", IE_Pressed, this, &AKawaiiPlayerCharacter::Victory);
	PlayerInputComponent->BindAction("HealthTest", IE_Pressed, this, &AKawaiiPlayerCharacter::DecreaseHealth);
	

	PlayerInputComponent->BindAxis("MoveForward", this, &AKawaiiPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKawaiiPlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AKawaiiPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AKawaiiPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AKawaiiPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AKawaiiPlayerCharacter::LookUpAtRate);
}

