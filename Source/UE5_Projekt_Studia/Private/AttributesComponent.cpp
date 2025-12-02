// Fill out your copyright notice in the Description page of Project Settings.

#include "ABasePlayerCharacter.h" 
#include "Enum/PawnState.h" 
#include "AttributesComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
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
    Stamina = MaxStamina;
}


void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (Stamina < MaxStamina)
    {
        if (AABasePlayerCharacter* PlayerChar = Cast<AABasePlayerCharacter>(GetOwner()))
        {
            float OldStamina = Stamina;
            EPawnState CurrentState = PlayerChar->GetCurrentPawnState();

            Stamina += StaminaCosts.StaminaRegenRate * DeltaTime;
            Stamina = FMath::Min(Stamina, MaxStamina);

            if (CurrentState == EPawnState::EPS_Exhausted)
            {
                if (Stamina > MaxStamina * 0.15f)
                {
                    PlayerChar->SetPawnState(EPawnState::EPS_Idle);
                    UE_LOG(LogTemp, Warning, TEXT("Stamina odzyskana. Ustawiam stan: Idle."));
                }
            }

            float Delta = Stamina - OldStamina;
            if (Delta > KINDA_SMALL_NUMBER)
            {
                OnStaminaChanged.Broadcast(this, Stamina, Delta, MaxStamina);
            }
        }
        else 
        {
            float OldStamina = Stamina;
            Stamina += StaminaCosts.StaminaRegenRate * DeltaTime;
            Stamina = FMath::Min(Stamina, MaxStamina);

            float Delta = Stamina - OldStamina;
            if (Delta > KINDA_SMALL_NUMBER)
            {
                OnStaminaChanged.Broadcast(this, Stamina, Delta, MaxStamina);
            }
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

    OnHealthChanged.Broadcast(this, Health, Delta, MaxHealth);

    if (Health == 0.0f)
    {
        OnDeath.Broadcast();
    }
}

bool UAttributesComponent::TryPayStaminaCost(float StaminaCost)
{
    if (CanPayStaminaCost(StaminaCost)) 
    {
        float OldStamina = Stamina;
        Stamina -= StaminaCost;
        Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);

        float Delta = Stamina - OldStamina;
        OnStaminaChanged.Broadcast(this, Stamina, Delta, MaxStamina);

        if (Stamina <= 0.0f)
        {
            OnStaminaExhausted.Broadcast(); 
        }

        return true;
    }
    return false;
}