#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Enum/PawnState.h" // Upewnij siê, ¿e œcie¿ka jest poprawna
#include "EnemyAIController.generated.h"

// Deklaracje wstêpne (Forward declarations)
class UBehaviorTree;
class UBlackboardData;

UCLASS()
class UE5_PROJEKT_STUDIA_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	// Funkcja wywo³ywana, gdy kontroler przejmuje w³adzê nad pionkiem
	virtual void OnPossess(APawn* InPawn) override;

	// Komponent zmys³ów (Wzrok)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	// Referencje do assetów (przypiszemy je potem w Blueprintcie)
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBlackboardData* BlackboardAsset;

	// --- KLUCZE BLACKBOARD (Nazwy musz¹ pasowaæ do tego, co stworzysz w Edytorze) ---
	const FName TargetActorKey = TEXT("TargetActor");
	const FName LastKnownPlayerLocationKey = TEXT("LastKnownPlayerLocation");
	const FName PawnStateKey = TEXT("PawnState");
	const FName IsDeadKey = TEXT("IsDead");
	const FName NextPatrolPointKey = TEXT("NextPatrolPoint");

protected:
	// Funkcja wywo³ywana, gdy percepcja coœ wykryje (lub zgubi)
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

public:
	// Pomocnicze funkcje do ustawiania wartoœci w Blackboard z poziomu C++
	void SetPawnStateInBlackboard(EPawnState NewState);
	void SetIsDeadInBlackboard(bool bIsDead);

	// Getter do Blackboarda
	FORCEINLINE class UBlackboardComponent* GetBlackboardComponent() const { return Blackboard; }
};