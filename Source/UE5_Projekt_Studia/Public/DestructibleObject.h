// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatInterface.h"
#include "DestructibleObject.generated.h"

UCLASS()
class ADestructibleObject : public AActor, public ICombatInterface
{
	GENERATED_BODY()

private:
	 int32 HitCount;

public:	
	// Sets default values for this actor's properties
	ADestructibleObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
