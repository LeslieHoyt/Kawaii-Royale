// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_PT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
	/* Behavior Tree component reference */
	UBehaviorTreeComponent* BehaviorComp;

	/* Blackboard comp ref */
	UBlackboardComponent* BlackboardComp;

public:
	AEnemyAIController();

	class AKawaiiCharacter* GetTargetEnemy();

	/* Blackboard key */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName BlackboardKey = "Target";

	/* Executes right when the controller posseses a pawn */
	virtual void OnPossess(APawn* Pawn) override;

	virtual void OnUnPossess() override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName TargetEnemyKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PatrolLocationKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName CurrentWaypointKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName BotTypeKeyName;

	void SetTargetEnemy(APawn* NewTarget);

	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	
	
};
