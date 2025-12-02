#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_AttackPlayer.generated.h"

UCLASS()
class UE5_PROJEKT_STUDIA_API UBTT_AttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_AttackPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};