// Fill out your copyright notice in the Description page of Project Settings.



#include "AttributesComponent.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{

    PrimaryComponentTick.bCanEverTick = false;

}


void UAttributesComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
}


void UAttributesComponent::ApplyDamage(float Damage)
{
    if (Health <= 0.0f || Damage <= 0.0f)
    {
        return;
    }
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

    if (Health == 0.0f)
    {
        OnDeath.Broadcast(); 
    }
}

void UAttributesComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    if (Health == 0.0f)
    {
        OnDeath.Broadcast();
    }
}