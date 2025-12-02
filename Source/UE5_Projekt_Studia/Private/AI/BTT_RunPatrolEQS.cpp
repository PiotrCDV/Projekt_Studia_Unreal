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
    APawn* PawnOwner = QueryOwner ? Cast<APawn>(QueryOwner) : nullptr;
    AAIController* AIController = PawnOwner ? Cast<AAIController>(PawnOwner->GetController()) : nullptr;

    if (!AIController) return;

    UBehaviorTreeComponent* BehaviorTreeComp = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent());
    if (!BehaviorTreeComp) return;

    if (Result->IsSuccessful() && Result->Items.Num() > 0)
    {


        int32 TotalItems = Result->Items.Num();
        int32 Range = FMath::Max(1, TotalItems / 4); 

        int32 RandomIndex = FMath::RandRange(0, Range - 1);

        FVector Location = Result->GetItemAsLocation(RandomIndex);


        BehaviorTreeComp->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Location);

        FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Succeeded);
    }
    else
    {
        FinishLatentTask(*BehaviorTreeComp, EBTNodeResult::Failed);
    }
}