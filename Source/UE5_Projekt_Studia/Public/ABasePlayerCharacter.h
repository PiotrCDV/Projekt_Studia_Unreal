// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "InputMappingContext.h"
#include "ABasePlayerCharacter.generated.h"

/**
 * 
 */
class InputMappingContext;
class UInputAction;

UCLASS()
class UE5_PROJEKT_STUDIA_API AABasePlayerCharacter : public AABaseCharacter
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
     UInputMappingContext* MappingContext;
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
     UInputAction* MoveAction;
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
     UInputAction* EquipAction;
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
     UInputAction* AttackAction;
	
};
