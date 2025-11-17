// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractionActor.h"

ABaseInteractionActor::ABaseInteractionActor()
{
	PrimaryActorTick.bCanEverTick = true;

}


void ABaseInteractionActor::Interact(AActor* Interactor)
{
	PickUp(Interactor);
}

void ABaseInteractionActor::PickUp(AActor* Interactor)
{

}

