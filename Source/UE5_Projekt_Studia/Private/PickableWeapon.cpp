// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableWeapon.h"
#include "ABasePlayerCharacter.h" // Dodaj ten include

APickableWeapon::APickableWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APickableWeapon::PickUp(AActor* Interactor)
{
	AABasePlayerCharacter* Player = Cast<AABasePlayerCharacter>(Interactor);
	if (Player)
	{
		Player->Equip(this);
		UE_LOG(LogTemp, Warning, TEXT("Wywo³ano Equip na Pawn z broni¹: %s"), *GetName());
	}
}

