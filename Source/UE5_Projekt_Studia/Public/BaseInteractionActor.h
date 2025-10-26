// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h" // Dodaj ten include
#include "BaseInteractionActor.generated.h"

UCLASS()
class UE5_PROJEKT_STUDIA_API ABaseInteractionActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Dodaj deklaracjê funkcji Interact z interfejsu
	virtual void Interact(AActor* Interactor) override;

	// Dodaj wirtualn¹ funkcjê PickUp
	virtual void PickUp(AActor* Interactor);
};
