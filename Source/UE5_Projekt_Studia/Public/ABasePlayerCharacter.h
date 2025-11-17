// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "ABasePlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UInteractionComponent;
class UAnimMontage;
class APickableWeapon;
struct FInputActionValue;

UCLASS()
class UE5_PROJEKT_STUDIA_API AABasePlayerCharacter : public AABaseCharacter
{
	GENERATED_BODY()

public:
    AABasePlayerCharacter();

    void StartWeaponTrace();
    void EndWeaponTrace();

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
     UInputMappingContext* MappingContext;
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
     UInputAction* MoveAction;
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
     UInputAction* EquipAction;
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
     UInputAction* AttackAction;
     UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
     UInputAction* LookAction;
     UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
     UInteractionComponent* InteractionComponent;
     UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
     APickableWeapon* CurrentWeapon;
     UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
     UAnimMontage* AttackMontage;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void Move(const FInputActionValue& Value);
    virtual void BeginPlay() override;
    void Look(const FInputActionValue& Value);
	virtual void Equip(APickableWeapon* Weapon);
    void Interact();
    void Attack(const FInputActionValue& Value);


protected:
    void PerformAttackTrace();


private:
    bool bIsAttacking;

    UPROPERTY()
    TArray<AActor*> HitActors;
};






