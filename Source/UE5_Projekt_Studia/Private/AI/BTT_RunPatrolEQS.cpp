#include "AI/BTT_RunPatrolEQS.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"

UBTT_RunPatrolEQS::UBTT_RunPatrolEQS()
{
	NodeName = "Run Patrol EQS";
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTT_RunPatrolEQS::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	if (!Controller || !EQSQuery)
	{
		return EBTNodeResult::Failed;
	}

	FEnvQueryRequest QueryRequest(EQSQuery, Controller->GetPawn());

	QueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &UBTT_RunPatrolEQS::OnQueryFinished);

	return EBTNodeResult::InProgress;
}
void UBTT_RunPatrolEQS::OnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{


    AActor* QueryOwner = Cast<AActor>(Result->Owner.Get());
    if (!QueryOwner) return;

    APawn* PawnOwner = Cast<APawn>(QueryOwner);
    if (!PawnOwner) return;

    AAIController* AIController = Cast<AAIController>(PawnOwner->GetController());
    if (!AIController) return;

    UBehaviorTreeComponent* BehaviorTreeComp = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());
    if (!BehaviorTreeComp) return;


    if (Result->IsSuccessful() && Result->Items.Num() > 0)
    {
        FVector Location = Result->GetItemAsLocation(0);
        BehaviorTreeComp->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location);

        FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Succeeded);
    }
    else
    {
        FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Failed);
    }
}