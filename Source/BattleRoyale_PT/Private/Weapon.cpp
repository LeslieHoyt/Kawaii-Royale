// Fill out your copyright notice in the Description page of Project Settings.

#define ECC_Player ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Enemy ECollisionChannel::ECC_GameTraceChannel2
#include "Weapon.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "KawaiiCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// basic setup
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(Root);
	// need to set collision this way to avoid launching player character into air
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	// box component
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CollisionMesh->SetRelativeLocation(FVector(-10, 40, 0));
	CollisionMesh->SetBoxExtent(FVector(14, 25, 5));
	CollisionMesh->bDynamicObstacle = true;
	CollisionMesh->SetupAttachment(Root);
	CollisionMesh->SetGenerateOverlapEvents(true);
	CollisionMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//CollisionMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	//CollisionMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//CollisionMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetSimulatePhysics(true);

	// need to set collision this way to avoid launching player character into air
	//WeaponMesh->SetCollisionObjectType(ECC_WorldDynamic);
	//WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	//WeaponMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//WeaponMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//WeaponMesh->SetNotifyRigidBodyCollision(true);
	//WeaponMesh->SetSimulatePhysics(true);

	// assign cleaver mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("'/Game/Yippy_Kawaii/Meshes/Accessories_mesh/SM_CleaverA.SM_CleaverA'"));
	UStaticMesh* Asset = MeshAsset.Object;
	WeaponMesh->SetStaticMesh(Asset);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent* AWeapon::GetCollisionMesh() const
{
	return CollisionMesh;
}

UStaticMeshComponent* AWeapon::GetWeaponMesh() const
{
	return WeaponMesh;
}

AKawaiiCharacter* AWeapon::GetPawnOwner() const
{
	return MyPawn;
}

void AWeapon::SetOwningPawn(AKawaiiCharacter* Owner)
{
	MyPawn = Owner;
	SetOwner(Owner);
}

void AWeapon::AttachMeshToPawn(AKawaiiCharacter* Pawn)
{
	if (Pawn)
	{
		USkeletalMeshComponent* PawnMesh = Pawn->GetMesh();
		WeaponMesh->AttachTo(PawnMesh, "hand_socket_r");
	}
}
