// Fill out your copyright notice in the Description page of Project Settings.

#include "AttributesComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
    // W³¹cz Tick, aby obs³ugiwaæ regeneracjê staminy
    PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.0f;
    MaxStamina = 100.0f;

    Health = MaxHealth;
    Stamina = MaxStamina;
}


void UAttributesComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
    Stamina = MaxStamina; // Inicjalizacja Staminy
}


void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Regeneracja staminy, jeœli nie jest pe³na
    if (Stamina < MaxStamina)
    {
        float OldStamina = Stamina;
        Stamina += StaminaCosts.StaminaRegenRate * DeltaTime;
        Stamina = FMath::Min(Stamina, MaxStamina);

        // Emisja delegata dla HUD
        float Delta = Stamina - OldStamina;
        if (Delta > KINDA_SMALL_NUMBER)
        {
            OnStaminaChanged.Broadcast(this, Stamina, Delta, MaxStamina);
        }
    }
}

void UAttributesComponent::ApplyDamage(float Damage)
{
    if (Health <= 0.0f || Damage <= 0.0f)
    {
        return;
    }

    float OldHealth = Health;
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    float Delta = Health - OldHealth;

    // Emisja delegata dla HUD (zdrowie spada)
    OnHealthChanged.Broadcast(this, Health, Delta, MaxHealth);

    if (Health == 0.0f)
    {
        OnDeath.Broadcast();
    }
}

void UAttributesComponent::SetHealth(float NewHealth)
{
    float OldHealth = Health;
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    float Delta = Health - OldHealth;

    // Emisja delegata dla HUD
    OnHealthChanged.Broadcast(this, Health, Delta, MaxHealth);

    if (Health == 0.0f)
    {
        OnDeath.Broadcast();
    }
}

// Funkcja sprawdzaj¹ca i zu¿ywaj¹ca staminê
bool UAttributesComponent::TryConsumeStamina(float StaminaCost)
{
    if (Stamina >= StaminaCost)
    {
        float OldStamina = Stamina;
        Stamina -= StaminaCost;

        // Emisja delegata dla HUD
        float Delta = Stamina - OldStamina;
        OnStaminaChanged.Broadcast(this, Stamina, Delta, MaxStamina);

        return true;
    }
    return false; // Brak staminy
}