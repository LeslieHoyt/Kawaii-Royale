// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "KawaiiEnemy.h"
#include "KawaiiCharacter.h"

AEnemyAIController::AEnemyAIController()
{
	// Initialize the behavior tree and blackboard components
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	/* Match with the AI/ZombieBlackboard */
	PatrolLocationKeyName = "PatrolLocation";
	CurrentWaypointKeyName = "CurrentWaypoint";
	BotTypeKeyName = "BotType";
	TargetEnemyKeyName = "TargetEnemy";
}

void AEnemyAIController::OnPossess(APawn* Pawn)
{
	Super::OnPossess(Pawn);
	// Get the possessed Pawn. If it's the AI Character we created
	// initialize it's blackboard and start it's corresponding behavior tree
	AKawaiiEnemy* AIEnemy = Cast<AKawaiiEnemy>(Pawn);
	if (AIEnemy)
	{
		if (AIEnemy->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AIEnemy->BehaviorTree->BlackboardAsset));
			BehaviorComp->StartTree(*AIEnemy->BehaviorTree);
		}
	}
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}

void AEnemyAIController::SetTargetEnemy(APawn* NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, NewTarget);
	}
}

AKawaiiCharacter* AEnemyAIController::GetTargetEnemy()
{
	if (BlackboardComp)
	{
		return Cast<AKawaiiCharacter>(BlackboardComp->GetValueAsObject(TargetEnemyKeyName));
	}
	return nullptr;
}
