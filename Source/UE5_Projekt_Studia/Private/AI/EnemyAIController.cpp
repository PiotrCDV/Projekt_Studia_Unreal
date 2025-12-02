#include "AI/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ABaseEnemyCharacter.h"
#include "ABasePlayerCharacter.h" 

AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);

	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SightConfig->SightRadius = 100.0f;       
		SightConfig->LoseSightRadius = 1000.0f;    
		SightConfig->PeripheralVisionAngleDegrees = 90.0f; 

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

		AIPerceptionComponent->ConfigureSense(*SightConfig);
		AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BlackboardAsset && BehaviorTreeAsset)
	{
	
		UBlackboardComponent* BlackboardComp;

		if (UseBlackboard(BlackboardAsset, BlackboardComp))
		{
			Blackboard = BlackboardComp;
			RunBehaviorTree(BehaviorTreeAsset);
		}
	}
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Blackboard) return;

	if (Actor && Actor->IsA<AABasePlayerCharacter>())
	{
		AABaseEnemyCharacter* EnemyPawn = Cast<AABaseEnemyCharacter>(GetPawn());

		if (Stimulus.WasSuccessfullySensed())
		{
			Blackboard->SetValueAsObject(TargetActorKey, Actor);
			Blackboard->ClearValue(LastKnownPlayerLocationKey); 

			if (EnemyPawn && EnemyPawn->GetPawnState() != EPawnState::EPS_HitReaction && EnemyPawn->GetPawnState() != EPawnState::EPS_Dead)
			{
				EnemyPawn->SyncPawnStateWithAI(EPawnState::EPS_InCombat);
			}
		}
		else
		{
		
			Blackboard->SetValueAsVector(LastKnownPlayerLocationKey, Stimulus.StimulusLocation);

			Blackboard->ClearValue(TargetActorKey);

			if (EnemyPawn && EnemyPawn->GetPawnState() != EPawnState::EPS_HitReaction && EnemyPawn->GetPawnState() != EPawnState::EPS_Dead)
			{
				EnemyPawn->SyncPawnStateWithAI(EPawnState::EPS_Idle);
			}
		}
	}
}

void AEnemyAIController::SetPawnStateInBlackboard(EPawnState NewState)
{
	if (Blackboard)
	{
		Blackboard->SetValueAsEnum(PawnStateKey, (uint8)NewState);
	}
}

void AEnemyAIController::SetIsDeadInBlackboard(bool bIsDead)
{
	if (Blackboard)
	{
		Blackboard->SetValueAsBool(IsDeadKey, bIsDead);
	}
}