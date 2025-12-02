#include "AI/BTT_AttackPlayer.h"
#include "AIController.h"
#include "ABaseEnemyCharacter.h"
#include "AttributesComponent.h"
#include "Enum/PawnState.h"

UBTT_AttackPlayer::UBTT_AttackPlayer()
{
	NodeName = "Attack Player"; // Nazwa widoczna w edytorze BT
}

EBTNodeResult::Type UBTT_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Pobieramy Kontroler i Pionka
	AAIController* Controller = OwnerComp.GetAIOwner();
	AABaseEnemyCharacter* EnemyPawn = Controller ? Cast<AABaseEnemyCharacter>(Controller->GetPawn()) : nullptr;

	if (!EnemyPawn)
	{
		return EBTNodeResult::Failed;
	}

	// Pobieramy komponent atrybutów
	UAttributesComponent* Attributes = EnemyPawn->GetAttributesComponent();
	float AttackCost = EnemyPawn->GetAttackStaminaCost();

	// PUNKT 120 i 122: Sprawdzamy i p³acimy stamin¹
	if (Attributes && Attributes->CanPayStaminaCost(AttackCost))
	{
		// 1. P³acimy koszt
		Attributes->TryPayStaminaCost(AttackCost);

		// 2. Ustawiamy stan na Atakowanie (¿eby nie przerwaæ animacji ruchem)
		EnemyPawn->SyncPawnStateWithAI(EPawnState::EPS_Attacking);

		// 3. Odpalamy animacjê ataku
		EnemyPawn->StartAttackFromAI();

		return EBTNodeResult::Succeeded;
	}
	else
	{
		// PUNKT 121: Brak staminy -> Stan Wyczerpania
		EnemyPawn->SyncPawnStateWithAI(EPawnState::EPS_Exhausted);

		return EBTNodeResult::Failed;
	}
}