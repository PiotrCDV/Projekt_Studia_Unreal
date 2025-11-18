// Fill out your copyright notice in the Description page of Project Settings.
// Plik: AttributesComponent.cpp (na górze)

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


// Plik: AttributesComponent.cpp

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
        else // Oryginalna logika, jeœli nie jesteœmy AABasePlayerCharacter (dla AI/NPC)
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

// Plik: AttributesComponent.cpp

// Funkcja sprawdzaj¹ca i zu¿ywaj¹ca staminê
bool UAttributesComponent::TryConsumeStamina(float StaminaCost)
{
    if (Stamina >= StaminaCost)
    {
        float OldStamina = Stamina;
        Stamina -= StaminaCost;
        Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina); // Zabezpieczenie przed ujemn¹ wartoœci¹

        // Emisja delegata dla HUD
        float Delta = Stamina - OldStamina;
        OnStaminaChanged.Broadcast(this, Stamina, Delta, MaxStamina);

        // --- DODANA LOGIKA WEJŒCIA W STAN WYCZERPANIA ---
        if (Stamina <= 0.0f)
        {
            // Rzutujemy na AABasePlayerCharacter (lub klasê, która ma SetPawnState)
            if (AABasePlayerCharacter* PlayerChar = Cast<AABasePlayerCharacter>(GetOwner()))
            {
                PlayerChar->SetPawnState(EPawnState::EPS_Exhausted);
                UE_LOG(LogTemp, Warning, TEXT("Stamina 0! Ustawiam stan: Exhausted."));
            }
        }
        // --------------------------------------------------

        return true;
    }
    return false; // Brak staminy
}