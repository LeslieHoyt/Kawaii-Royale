// Fill out your copyright notice in the Description page of Project Settings.

#define ECC_Player ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Enemy ECollisionChannel::ECC_GameTraceChannel2
#include "KawaiiEnemy.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Animation/AnimBlueprint.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"

// Sets default values
AKawaiiEnemy::AKawaiiEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weapon = NULL;

	// set initial appearance
	RandomizeAppearance();

	/* Set animation blueprint */
	// Load the animation blueprint
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("'/Game/NPC/AnimBP_KawaiiEnemy.AnimBP_KawaiiEnemy'"));
	// Generated class is important here
	GetMesh()->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);
	GetMesh()->SetCollisionObjectType(ECC_Enemy);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	/* Our sensing component to detect players by visibility and noise checks */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	// Set the peripheral vision angle to 60 degrees
	PawnSensingComp->SetPeripheralVisionAngle(60.f);
	PawnSensingComp->SightRadius = 2000;
	//PawnSensingComp->HearingThreshold = 600;
	//PawnSensingComp->LOSHearingThreshold = 1200;
}

// Called when the game starts or when spawned
void AKawaiiEnemy::BeginPlay()
{
	Super::BeginPlay();

	// collision setup
	GetMeleeCollisionComp()->SetCollisionResponseToChannel(ECC_Player, ECR_Overlap);
	Weapon->GetCollisionMesh()->SetCollisionObjectType(ECC_Enemy);
	Weapon->GetCollisionMesh()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Ignore);
	GetMeleeCollisionComp()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Ignore);

	// Register the function that is going to fire when the character sees a Pawn
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AKawaiiEnemy::OnSeePlayer);
	}
}

void AKawaiiEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AKawaiiEnemy::OnSeePlayer(APawn* Pawn)
{
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	// Set the seen target on the blackboard
	if (AIController)
	{
		GLog->Log("Oh hello there");
		AIController->SetTargetEnemy(Pawn);
	}
}

// Called every frame
void AKawaiiEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKawaiiEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AKawaiiEnemy::RandomizeAppearance()
{
	// Randomize mesh
	int32 meshType = FMath::RandRange(0, 2);
	if (meshType == 0)
	{
		// bear
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset1(TEXT("'/Game/Yippy_Kawaii/Meshes/Characters_meshes/SM_Bear.SM_Bear'"));
		if (MeshAsset1.Succeeded())
		{
			MeshContainer = MeshAsset1.Object;
			GetMesh()->SetSkeletalMesh(MeshContainer);
			// Randomize mesh material
			int32 materialType = FMath::RandRange(0, 14);
			if (materialType == 0)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear0(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_0.M_Bear_0'"));
				if (MaterialBear0.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear0.Object, MaterialBear0.Object));
				}
			}
			else if (materialType == 1)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear1(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_1.M_Bear_1'"));
				if (MaterialBear1.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear1.Object, MaterialBear1.Object));
				}
			}
			else if (materialType == 2)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear2(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_2.M_Bear_2'"));
				if (MaterialBear2.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear2.Object, MaterialBear2.Object));
				}
			}
			else if (materialType == 3)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear3(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_3.M_Bear_3'"));
				if (MaterialBear3.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear3.Object, MaterialBear3.Object));
				}
			}
			else if (materialType == 4)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear4(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_4.M_Bear_4'"));
				if (MaterialBear4.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear4.Object, MaterialBear4.Object));
				}
			}
			else if (materialType == 5)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear5(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_5.M_Bear_5'"));
				if (MaterialBear5.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear5.Object, MaterialBear5.Object));
				}
			}
			else if (materialType == 6)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear6(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_6.M_Bear_6'"));
				if (MaterialBear6.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear6.Object, MaterialBear6.Object));
				}
			}
			else if (materialType == 7)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear7(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_7.M_Bear_7'"));
				if (MaterialBear7.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear7.Object, MaterialBear7.Object));
				}
			}
			else if (materialType == 8)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear8(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_8.M_Bear_8'"));
				if (MaterialBear8.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear8.Object, MaterialBear8.Object));
				}
			}
			else if (materialType == 9)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear9(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_9.M_Bear_9'"));
				if (MaterialBear9.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear9.Object, MaterialBear9.Object));
				}
			}
			else if (materialType == 10)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear10(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_10.M_Bear_10'"));
				if (MaterialBear10.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear10.Object, MaterialBear10.Object));
				}
			}
			else if (materialType == 11)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear11(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_11.M_Bear_11'"));
				if (MaterialBear11.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear11.Object, MaterialBear11.Object));
				}
			}
			else if (materialType == 12)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear12(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_12.M_Bear_12'"));
				if (MaterialBear12.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear12.Object, MaterialBear12.Object));
				}
			}
			else if (materialType == 13)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear13(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_13.M_Bear_13'"));
				if (MaterialBear13.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear13.Object, MaterialBear13.Object));
				}
			}
			else
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBear14(TEXT("'/Game/Yippy_Kawaii/Materials/Bear_Materials/M_Bear_14.M_Bear_14'"));
				if (MaterialBear14.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBear14.Object, MaterialBear14.Object));
				}
			}
		}
	}
	else if (meshType == 1)
	{
		// bunny
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset2(TEXT("'/Game/Yippy_Kawaii/Meshes/Characters_meshes/SM_Bunny.SM_Bunny'"));
		if (MeshAsset2.Succeeded())
		{
			MeshContainer = MeshAsset2.Object;
			GetMesh()->SetSkeletalMesh(MeshContainer);
			// Randomize mesh material
			int32 materialType = FMath::RandRange(0, 14);
			if (materialType == 0)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny0(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_0.M_Bunny_0'"));
				if (MaterialBunny0.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny0.Object, MaterialBunny0.Object));
				}
			}
			else if (materialType == 1)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny1(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_1.M_Bunny_1'"));
				if (MaterialBunny1.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny1.Object, MaterialBunny1.Object));
				}
			}
			else if (materialType == 2)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny2(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_2.M_Bunny_2'"));
				if (MaterialBunny2.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny2.Object, MaterialBunny2.Object));
				}
			}
			else if (materialType == 3)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny3(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_3.M_Bunny_3'"));
				if (MaterialBunny3.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny3.Object, MaterialBunny3.Object));
				}
			}
			else if (materialType == 4)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny4(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_4.M_Bunny_4'"));
				if (MaterialBunny4.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny4.Object, MaterialBunny4.Object));
				}
			}
			else if (materialType == 5)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny5(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_5.M_Bunny_5'"));
				if (MaterialBunny5.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny5.Object, MaterialBunny5.Object));
				}
			}
			else if (materialType == 6)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny6(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_6.M_Bunny_6'"));
				if (MaterialBunny6.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny6.Object, MaterialBunny6.Object));
				}
			}
			else if (materialType == 7)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny7(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_7.M_Bunny_7'"));
				if (MaterialBunny7.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny7.Object, MaterialBunny7.Object));
				}
			}
			else if (materialType == 8)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny8(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_8.M_Bunny_8'"));
				if (MaterialBunny8.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny8.Object, MaterialBunny8.Object));
				}
			}
			else if (materialType == 9)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny9(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_9.M_Bunny_9'"));
				if (MaterialBunny9.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny9.Object, MaterialBunny9.Object));
				}
			}
			else if (materialType == 10)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny10(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_10.M_Bunny_10'"));
				if (MaterialBunny10.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny10.Object, MaterialBunny10.Object));
				}
			}
			else if (materialType == 11)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny11(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_11.M_Bunny_11'"));
				if (MaterialBunny11.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny11.Object, MaterialBunny11.Object));
				}
			}
			else if (materialType == 12)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny12(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_12.M_Bunny_12'"));
				if (MaterialBunny12.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny12.Object, MaterialBunny12.Object));
				}
			}
			else if (materialType == 13)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny13(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_13.M_Bunny_13'"));
				if (MaterialBunny13.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny13.Object, MaterialBunny13.Object));
				}
			}
			else
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialBunny14(TEXT("'/Game/Yippy_Kawaii/Materials/Bunny_Materials/M_Bunny_14.M_Bunny_14'"));
				if (MaterialBunny14.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialBunny14.Object, MaterialBunny14.Object));
				}
			}
		}
	}
	else
	{
		// cat
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset3(TEXT("'/Game/Yippy_Kawaii/Meshes/Characters_meshes/SM_Cat.SM_Cat'"));
		if (MeshAsset3.Succeeded())
		{
			MeshContainer = MeshAsset3.Object;
			GetMesh()->SetSkeletalMesh(MeshContainer);
			// Randomize mesh material
			int32 materialType = FMath::RandRange(0, 14);
			if (materialType == 0)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat0(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_0.M_Cat_0'"));
				if (MaterialCat0.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat0.Object, MaterialCat0.Object));
				}
			}
			else if (materialType == 1)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat1(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_1.M_Cat_1'"));
				if (MaterialCat1.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat1.Object, MaterialCat1.Object));
				}
			}
			else if (materialType == 2)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat2(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_2.M_Cat_2'"));
				if (MaterialCat2.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat2.Object, MaterialCat2.Object));
				}
			}
			else if (materialType == 3)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat3(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_3.M_Cat_3'"));
				if (MaterialCat3.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat3.Object, MaterialCat3.Object));
				}
			}
			else if (materialType == 4)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat4(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_4.M_Cat_4'"));
				if (MaterialCat4.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat4.Object, MaterialCat4.Object));
				}
			}
			else if (materialType == 5)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat5(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_5.M_Cat_5'"));
				if (MaterialCat5.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat5.Object, MaterialCat5.Object));
				}
			}
			else if (materialType == 6)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat6(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_6.M_Cat_6'"));
				if (MaterialCat6.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat6.Object, MaterialCat6.Object));
				}
			}
			else if (materialType == 7)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat7(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_7.M_Cat_7'"));
				if (MaterialCat7.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat7.Object, MaterialCat7.Object));
				}
			}
			else if (materialType == 8)
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat8(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_8.M_Cat_8'"));
				if (MaterialCat8.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat8.Object, MaterialCat8.Object));
				}
			}
			else
			{
				static ConstructorHelpers::FObjectFinder<UMaterial> MaterialCat14(TEXT("'/Game/Yippy_Kawaii/Materials/Cat_Materials/M_Cat_14.M_Cat_14'"));
				if (MaterialCat14.Succeeded())
				{
					GetMesh()->SetMaterial(0, UMaterialInstanceDynamic::Create(MaterialCat14.Object, MaterialCat14.Object));
				}
			}
		}
	}

	// Randomize face
	int32 faceType = FMath::RandRange(1, 28);
	if (faceType == 1)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace1(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_1.M_Face_1'"));
		if (MaterialFace1.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace1.Object, MaterialFace1.Object));
		}
	}
	else if (faceType == 2)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace2(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_2.M_Face_2'"));
		if (MaterialFace2.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace2.Object, MaterialFace2.Object));
		}
	}
	else if (faceType == 3)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace3(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_3.M_Face_3'"));
		if (MaterialFace3.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace3.Object, MaterialFace3.Object));
		}
	}
	else if (faceType == 4)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace4(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_4.M_Face_4'"));
		if (MaterialFace4.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace4.Object, MaterialFace4.Object));
		}
	}
	else if (faceType == 5)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace5(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_5.M_Face_5'"));
		if (MaterialFace5.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace5.Object, MaterialFace5.Object));
		}
	}
	else if (faceType == 6)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace6(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_6.M_Face_6'"));
		if (MaterialFace6.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace6.Object, MaterialFace6.Object));
		}
	}
	else if (faceType == 7)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace7(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_7.M_Face_7'"));
		if (MaterialFace7.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace7.Object, MaterialFace7.Object));
		}
	}
	else if (faceType == 8)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace8(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_8.M_Face_8'"));
		if (MaterialFace8.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace8.Object, MaterialFace8.Object));
		}
	}
	else if (faceType == 9)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace9(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_9.M_Face_9'"));
		if (MaterialFace9.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace9.Object, MaterialFace9.Object));
		}
	}
	else if (faceType == 10)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace10(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_10.M_Face_10'"));
		if (MaterialFace10.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace10.Object, MaterialFace10.Object));
		}
	}
	else if (faceType == 11)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace11(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_11.M_Face_11'"));
		if (MaterialFace11.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace11.Object, MaterialFace11.Object));
		}
	}
	else if (faceType == 12)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace12(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_12.M_Face_12'"));
		if (MaterialFace12.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace12.Object, MaterialFace12.Object));
		}
	}
	else if (faceType == 13)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace13(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_13.M_Face_13'"));
		if (MaterialFace13.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace13.Object, MaterialFace13.Object));
		}
	}
	else if (faceType == 14)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace14(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_14.M_Face_14'"));
		if (MaterialFace14.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace14.Object, MaterialFace14.Object));
		}
	}
	else if (faceType == 15)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace15(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_15.M_Face_15'"));
		if (MaterialFace15.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace15.Object, MaterialFace15.Object));
		}
	}
	else if (faceType == 16)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace16(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_16.M_Face_16'"));
		if (MaterialFace16.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace16.Object, MaterialFace16.Object));
		}
	}
	else if (faceType == 17)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace17(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_17.M_Face_17'"));
		if (MaterialFace17.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace17.Object, MaterialFace17.Object));
		}
	}
	else if (faceType == 18)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace18(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_18.M_Face_18'"));
		if (MaterialFace18.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace18.Object, MaterialFace18.Object));
		}
	}
	else if (faceType == 19)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace19(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_19.M_Face_19'"));
		if (MaterialFace19.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace19.Object, MaterialFace19.Object));
		}
	}
	else if (faceType == 20)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace20(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_20.M_Face_20'"));
		if (MaterialFace20.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace20.Object, MaterialFace20.Object));
		}
	}
	else if (faceType == 21)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace21(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_21.M_Face_21'"));
		if (MaterialFace21.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace21.Object, MaterialFace21.Object));
		}
	}
	else if (faceType == 22)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace22(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_22.M_Face_22'"));
		if (MaterialFace22.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace22.Object, MaterialFace22.Object));
		}
	}
	else if (faceType == 23)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace23(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_23.M_Face_23'"));
		if (MaterialFace23.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace23.Object, MaterialFace23.Object));
		}
	}
	else if (faceType == 24)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace24(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_24.M_Face_24'"));
		if (MaterialFace24.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace24.Object, MaterialFace24.Object));
		}
	}
	else if (faceType == 25)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace25(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_25.M_Face_25'"));
		if (MaterialFace25.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace25.Object, MaterialFace25.Object));
		}
	}
	else if (faceType == 26)
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace26(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_26.M_Face_26'"));
		if (MaterialFace26.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace26.Object, MaterialFace26.Object));
		}
	}
	else
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFace27(TEXT("'/Game/Yippy_Kawaii/Materials/Faces_Materials/M_Face_27.M_Face_27'"));
		if (MaterialFace27.Succeeded())
		{
			GetMesh()->SetMaterial(1, UMaterialInstanceDynamic::Create(MaterialFace27.Object, MaterialFace27.Object));
		}
	}
}
