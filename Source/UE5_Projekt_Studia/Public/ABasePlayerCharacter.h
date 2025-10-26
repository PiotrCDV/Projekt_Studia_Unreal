// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "InteractionComponent.h"
#include "InputMappingContext.h"
#include "PickableWeapon.h"
#include "ABasePlayerCharacter.generated.h"

UCLASS()
class UE5_PROJEKT_STUDIA_API AABasePlayerCharacter : public AABaseCharacter
{
	GENERATED_BODY()

public:
    AABasePlayerCharacter();

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

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void Move(const FInputActionValue& Value);
    virtual void BeginPlay() override;
    void Look(const FInputActionValue& Value);
	virtual void Equip(APickableWeapon* Weapon);
    void Interact();
};




