#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Enum/PawnState.h" 
#include "EnemyAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;

UCLASS()
class UE5_PROJEKT_STUDIA_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBlackboardData* BlackboardAsset;

	const FName TargetActorKey = TEXT("TargetActor");
	const FName LastKnownPlayerLocationKey = TEXT("LastKnownPlayerLocation");
	const FName PawnStateKey = TEXT("PawnState");
	const FName IsDeadKey = TEXT("IsDead");
	const FName NextPatrolPointKey = TEXT("NextPatrolPoint");

protected:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

public:
	void SetPawnStateInBlackboard(EPawnState NewState);
	void SetIsDeadInBlackboard(bool bIsDead);

	FORCEINLINE class UBlackboardComponent* GetBlackboardComponent() const { return Blackboard; }
};