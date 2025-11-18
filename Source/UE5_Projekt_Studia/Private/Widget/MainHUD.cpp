// Plik: UMainHUD.cpp

#include "Widget/MainHUD.h"
#include "Components/TextBlock.h" // Wymagany do u¿ycia UTextBlock
#include "Enum/PawnState.h"      // Wymagany do u¿ycia EPawnState
#include "Components/ProgressBar.h" // Upewnij siê, ¿e ten jest, jeœli nie jest w prekompilacji

void UMainHUD::UpdateHealth(float Current, float Max)
{
    if (HealthBar && Max > 0)
    {
        HealthBar->SetPercent(Current / Max);
    }
}

void UMainHUD::UpdateStamina(float Current, float Max)
{
    if (StaminaBar && Max > 0)
    {
        StaminaBar->SetPercent(Current / Max);
    }
}

// -----------------------------------------------------------------------------------
// IMPLEMENTACJA PUNKTU 5 (WIZUALNA INFORMACJA ZWROTNA - HUD)
// -----------------------------------------------------------------------------------

FString UMainHUD::GetPawnStateString(EPawnState State) const
{
    switch (State)
    {
    case EPawnState::EPS_Idle:
        return TEXT("IDLE");
    case EPawnState::EPS_InCombat:
        return TEXT("WALKA");
    case EPawnState::EPS_HitReaction:
        return TEXT("UDERZENIE");
    case EPawnState::EPS_Attacking:
        return TEXT("ATAK");
    case EPawnState::EPS_Exhausted:
        return TEXT("WYCZERPANY!");
    case EPawnState::EPS_Dead:
        return TEXT("MARTWY");
    default:
        return TEXT("NIEZNANY");
    }
}

void UMainHUD::HandlePawnStateUpdate(EPawnState NewState)
{
    // 1. Aktualizacja tekstu
    if (StateText)
    {
        FString NewText = GetPawnStateString(NewState);
        StateText->SetText(FText::FromString(NewText));

        // 2. Aktualizacja koloru
        FSlateColor NewColor;

        if (NewState == EPawnState::EPS_Exhausted || NewState == EPawnState::EPS_Dead)
        {
            // Czerwony dla stanu krytycznego (Wyczerpanie, Œmieræ)
            NewColor = FSlateColor(FLinearColor::Red);
        }
        else if (NewState == EPawnState::EPS_InCombat || NewState == EPawnState::EPS_Attacking)
        {
            // ¯ó³ty dla stanów walki
            NewColor = FSlateColor(FLinearColor::Yellow);
        }
        else if (NewState == EPawnState::EPS_HitReaction)
        {
            // Pomarañczowy dla reakcji na obra¿enia
            NewColor = FSlateColor(FLinearColor(1.0f, 0.5f, 0.0f)); // Pomarañczowy
        }
        else
        {
            // Bia³y dla domyœlnych stanów (IDLE)
            NewColor = FSlateColor(FLinearColor::White);
        }

        StateText->SetColorAndOpacity(NewColor);
    }
}