// Fill out your copyright notice in the Description page of Project Settings.

#include "ABasePlayerCharacter.h" // Lub ABaseCharacter, jeœli stany s¹ tam zaimplementowane
#include "Enum/PawnState.h" // Upewnij siê, ¿e masz ten plik dla EPawnState
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

    if (Stamina < MaxStamina)
    {
        // --- LOGIKA STANU I REGENERACJI ---
        if (AABasePlayerCharacter* PlayerChar = Cast<AABasePlayerCharacter>(GetOwner()))
        {
            float OldStamina = Stamina;
            EPawnState CurrentState = PlayerChar->GetCurrentPawnState();

            // 1. Regeneracja jest aktywna niezale¿nie od stanu, by móc z niego wyjœæ
            Stamina += StaminaCosts.StaminaRegenRate * DeltaTime;
            Stamina = FMath::Min(Stamina, MaxStamina);

            // 2. Warunek wyjœcia ze stanu
            if (CurrentState == EPawnState::EPS_Exhausted)
            {
                // Wychodzimy ze stanu, gdy zregeneruje siê do 15% MaxStaminy
                if (Stamina > MaxStamina * 0.15f)
                {
                    // U¿ywamy SetPawnState z klasy AABasePlayerCharacter
                    PlayerChar->SetPawnState(EPawnState::EPS_Idle);
                    UE_LOG(LogTemp, Warning, TEXT("Stamina odzyskana. Ustawiam stan: Idle."));
                }
            }

            // 3. Emisja delegata dla HUD
            float Delta = Stamina - OldStamina;
            if (Delta > KINDA_SMALL_NUMBER)
            {
                OnStaminaChanged.Broadcast(this, Stamina, Delta, MaxStamina);
            }
        }
        else // Logika dla AI/NPC, która nie jest AABasePlayerCharacter
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

// Funkcja sprawdzaj¹ca i zu¿ywaj¹ca staminê (Zmieniona nazwa)
bool UAttributesComponent::TryPayStaminaCost(float StaminaCost)
{
    if (CanPayStaminaCost(StaminaCost)) // U¿ywamy nowej funkcji CanPayStaminaCost (Punkt 120)
    {
        float OldStamina = Stamina;
        Stamina -= StaminaCost;
        Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);

        // Emisja delegata dla HUD
        float Delta = Stamina - OldStamina;
        OnStaminaChanged.Broadcast(this, Stamina, Delta, MaxStamina);

        // --- LOGIKA WEJŒCIA W STAN WYCZERPANIA ---
        if (Stamina <= 0.0f)
        {
            OnStaminaExhausted.Broadcast(); // Wywo³anie delegata (Punkt 121)
        }
        // --------------------------------------------------

        return true;
    }
    return false; // Brak staminy
}