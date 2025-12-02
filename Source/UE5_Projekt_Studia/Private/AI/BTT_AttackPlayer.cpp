#include "AI/BTT_AttackPlayer.h"
#include "AIController.h"
#include "ABaseEnemyCharacter.h"
#include "AttributesComponent.h"
#include "Enum/PawnState.h"

UBTT_AttackPlayer::UBTT_AttackPlayer()
{
	NodeName = "Attack Player"; 
}

EBTNodeResult::Type UBTT_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	AABaseEnemyCharacter* EnemyPawn = Controller ? Cast<AABaseEnemyCharacter>(Controller->GetPawn()) : nullptr;

	if (!EnemyPawn)
	{
		return EBTNodeResult::Failed;
	}

	UAttributesComponent* Attributes = EnemyPawn->GetAttributesComponent();
	float AttackCost = EnemyPawn->GetAttackStaminaCost();

	if (Attributes && Attributes->CanPayStaminaCost(AttackCost))
	{
		Attributes->TryPayStaminaCost(AttackCost);

		EnemyPawn->SyncPawnStateWithAI(EPawnState::EPS_Attacking);

		EnemyPawn->StartAttackFromAI();

		return EBTNodeResult::Succeeded;
	}
	else
	{
		EnemyPawn->SyncPawnStateWithAI(EPawnState::EPS_Exhausted);

		return EBTNodeResult::Failed;
	}
}