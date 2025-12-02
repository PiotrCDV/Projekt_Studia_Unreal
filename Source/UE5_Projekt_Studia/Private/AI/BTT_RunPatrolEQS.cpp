#include "AI/BTT_RunPatrolEQS.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"

UBTT_RunPatrolEQS::UBTT_RunPatrolEQS()
{
	NodeName = "Run Patrol EQS";
	bNotifyTaskFinished = true; // Wa¿ne: Task nie koñczy siê natychmiast, czeka na wynik EQS
}

EBTNodeResult::Type UBTT_RunPatrolEQS::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	if (!Controller || !EQSQuery)
	{
		return EBTNodeResult::Failed;
	}

	// PUNKT 80: Uruchamiamy zapytanie EQS
	FEnvQueryRequest QueryRequest(EQSQuery, Controller->GetPawn());

	// Mówimy: "Jak skoñczysz, wywo³aj funkcjê OnQueryFinished w tym obiekcie (this)"
	QueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &UBTT_RunPatrolEQS::OnQueryFinished);

	return EBTNodeResult::InProgress;
}
void UBTT_RunPatrolEQS::OnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
    // ... (pocz¹tek funkcji bez zmian: pobieranie QueryOwner, PawnOwner, AIController) ...
    // ... (pobieranie BehaviorTreeComp bez zmian) ...

    AActor* QueryOwner = Cast<AActor>(Result->Owner.Get());
    if (!QueryOwner) return;

    APawn* PawnOwner = Cast<APawn>(QueryOwner);
    if (!PawnOwner) return;

    AAIController* AIController = Cast<AAIController>(PawnOwner->GetController());
    if (!AIController) return;

    UBehaviorTreeComponent* BehaviorTreeComp = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());
    if (!BehaviorTreeComp) return;

    // --- POPRAWKA PONI¯EJ ---

    if (Result->IsSuccessful() && Result->Items.Num() > 0)
    {
        FVector Location = Result->GetItemAsLocation(0);
        BehaviorTreeComp->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location);

        // ZMIANA: Podajemy *BehaviorTreeComp zamiast kontrolera
        FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Succeeded);
    }
    else
    {
        // ZMIANA: Tutaj tak samo, podajemy *BehaviorTreeComp
        FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Failed);
    }
}