// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "CombatInterface.h"
#include "Enum/PawnState.h" 
#include "Animation/AnimMontage.h"
#include "ABaseEnemyCharacter.generated.h"

class UAttributesComponent;
class APickableWeapon;

UCLASS()
class UE5_PROJEKT_STUDIA_API AABaseEnemyCharacter : public AABaseCharacter, public ICombatInterface
{
    GENERATED_BODY()

public:
    AABaseEnemyCharacter();

    virtual void GetHit_Implementation(AActor* Attacker, float Damage) override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SetPawnState(EPawnState NewState);

    UFUNCTION(BlueprintPure, Category = "Combat")
    EPawnState GetPawnState() const { return CurrentPawnState; }

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void TryAttack();
    void AttackFinished();
    void AttackCanceled();

    FTimerHandle AttackTimerHandle;

    UFUNCTION()
    void CheckForPlayerAndAttack();

    void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack")
    float AttackRange = 250.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    AABaseCharacter* PlayerTarget = nullptr;

    UFUNCTION()
    void HandleDeath();
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Combat")
    APickableWeapon* EquippedWeapon;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<APickableWeapon> DefaultWeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    FName WeaponSocketName = TEXT("WeaponSocket");
};