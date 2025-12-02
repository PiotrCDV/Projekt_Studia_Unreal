#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h" 
#include "BTT_RunPatrolEQS.generated.h"

UCLASS()
class UE5_PROJEKT_STUDIA_API UBTT_RunPatrolEQS : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_RunPatrolEQS();

	UPROPERTY(EditAnywhere, Category = "EQS")
	class UEnvQuery* EQSQuery;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	void OnQueryFinished(TSharedPtr<FEnvQueryResult> Result);
};