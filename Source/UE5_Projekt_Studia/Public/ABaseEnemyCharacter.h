#pragma once

#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "CombatInterface.h"
#include "Enum/PawnState.h" 
#include "Animation/AnimMontage.h"
#include "ABaseEnemyCharacter.generated.h"

class UAttributesComponent;
class APickableWeapon;
class AEnemyAIController; // Forward declaration nowej klasy

UCLASS()
class UE5_PROJEKT_STUDIA_API AABaseEnemyCharacter : public AABaseCharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AABaseEnemyCharacter();

	virtual void GetHit_Implementation(AActor* Attacker, float Damage) override;

	// Funkcje zmiany stanu
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetPawnState(EPawnState NewState);

	UFUNCTION(BlueprintPure, Category = "Combat")
	EPawnState GetPawnState() const { return CurrentPawnState; }

protected:
	virtual void BeginPlay() override;

	// Logika zakoñczenia animacji (Ataku lub HitReact)
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// --- INTEGRACJA Z AI ---

	// Synchronizuje stan (zmienna w klasie + Blackboard w kontrolerze)
public: void SyncPawnStateWithAI(EPawnState NewState);

	  // Wywo³ywana przez Behavior Tree Task, ¿eby zacz¹æ machaæ mieczem
	  UFUNCTION(BlueprintCallable, Category = "AI")
	  void StartAttackFromAI();

	  // Wywo³ywana przez AttributesComponent, gdy stamina spadnie do 0
	  UFUNCTION()
	  void HandleStaminaExhausted();

	  // Referencja do naszego nowego kontrolera
	  UPROPERTY()
	  class AEnemyAIController* AIController;

	  // Koszt staminy potrzebny do wykonania ataku
	  UPROPERTY(EditDefaultsOnly, Category = "Combat")
	  float AttackStaminaCost = 25.0f;

	  // Gettery dla Tasków BT
	  FORCEINLINE class UAttributesComponent* GetAttributesComponent() const { return AttributesComponent; }
	  FORCEINLINE float GetAttackStaminaCost() const { return AttackStaminaCost; }


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAttributesComponent* AttributesComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	EPawnState CurrentPawnState;

	// Zasiêg ataku (u¿ywany teraz w Behavior Tree, ale warto zostawiæ zmienn¹)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack")
	float AttackRange = 250.0f;

	UFUNCTION()
	void HandleDeath();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Combat")
	APickableWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<APickableWeapon> DefaultWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName WeaponSocketName = TEXT("WeaponSocket");
};