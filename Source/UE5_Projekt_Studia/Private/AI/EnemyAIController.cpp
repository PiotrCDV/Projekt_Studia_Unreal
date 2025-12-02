#include "AI/EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ABaseEnemyCharacter.h"
#include "ABasePlayerCharacter.h" // Potrzebne, ¿eby rozpoznaæ gracza

AEnemyAIController::AEnemyAIController()
{
	// 1. Tworzenie komponentu percepcji
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);

	// 2. Konfiguracja zmys³u wzroku (Sight)
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SightConfig->SightRadius = 1500.0f;        // Jak daleko widzi (zielony okr¹g)
		SightConfig->LoseSightRadius = 2000.0f;    // Kiedy traci cel z oczu (ró¿owy okr¹g)
		SightConfig->PeripheralVisionAngleDegrees = 90.0f; // K¹t widzenia

		// Wykrywaj wszystkich (wrogów, neutralnych, przyjació³)
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

		AIPerceptionComponent->ConfigureSense(*SightConfig);
		AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

		// Pod³¹czenie funkcji do zdarzenia wykrycia
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 3. Uruchomienie logicznego mózgu (Behavior Tree)
	if (BlackboardAsset && BehaviorTreeAsset)
	{
		// --- POPRAWKA DLA UE5 ---
		// Tworzymy tymczasowy zwyk³y wskaŸnik
		UBlackboardComponent* BlackboardComp;

		// Przekazujemy ten tymczasowy wskaŸnik do funkcji
		if (UseBlackboard(BlackboardAsset, BlackboardComp))
		{
			// A na koniec przypisujemy go do zmiennej klasowej "Blackboard"
			Blackboard = BlackboardComp;
			RunBehaviorTree(BehaviorTreeAsset);
		}
	}
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Blackboard) return;

	// Reagujemy tylko, jeœli wykryty obiekt to Gracz (AABasePlayerCharacter)
	if (Actor && Actor->IsA<AABasePlayerCharacter>())
	{
		// Pobieramy naszego pionka, ¿eby zaktualizowaæ jego stan
		AABaseEnemyCharacter* EnemyPawn = Cast<AABaseEnemyCharacter>(GetPawn());

		if (Stimulus.WasSuccessfullySensed())
		{
			// --- WIDZÊ GRACZA ---
			Blackboard->SetValueAsObject(TargetActorKey, Actor);
			Blackboard->ClearValue(LastKnownPlayerLocationKey); // Czyœcimy star¹ pozycjê, bo widzimy go na ¿ywo

			// Zmieniamy stan na walkê (jeœli nie jest martwy/trafiony)
			if (EnemyPawn && EnemyPawn->GetPawnState() != EPawnState::EPS_HitReaction && EnemyPawn->GetPawnState() != EPawnState::EPS_Dead)
			{
				EnemyPawn->SyncPawnStateWithAI(EPawnState::EPS_InCombat);
			}
		}
		else
		{
			// --- ZGUBI£EM GRACZA ---
			// Zapamiêtaj gdzie go ostatnio widzia³eœ
			Blackboard->SetValueAsVector(LastKnownPlayerLocationKey, Stimulus.StimulusLocation);

			// Wyczyœæ cel (nie widzisz go ju¿ bezpoœrednio)
			Blackboard->ClearValue(TargetActorKey);

			// Wróæ do stanu Idle (Behavior Tree przejdzie wtedy do ga³êzi Szukania)
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