// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractionActor.h"
#include "PickableWeapon.generated.h"

UCLASS()
class UE5_PROJEKT_STUDIA_API APickableWeapon : public ABaseInteractionActor
{
	GENERATED_BODY()

public:
	APickableWeapon();

	virtual void PickUp(AActor* Interactor) override;
};
