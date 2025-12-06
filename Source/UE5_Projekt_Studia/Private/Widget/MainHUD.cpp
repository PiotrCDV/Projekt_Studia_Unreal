// Plik: UMainHUD.cpp

#include "Widget/MainHUD.h"
#include "TimerManager.h"
#include "Components/TextBlock.h" 
#include "Enum/PawnState.h"     
#include "Components/ProgressBar.h" 

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
    if (StateText)
    {
        FString NewText = GetPawnStateString(NewState);
        StateText->SetText(FText::FromString(NewText));

        FSlateColor NewColor;

        if (NewState == EPawnState::EPS_Exhausted || NewState == EPawnState::EPS_Dead)
        {
            NewColor = FSlateColor(FLinearColor::Red);
        }
        else if (NewState == EPawnState::EPS_InCombat || NewState == EPawnState::EPS_Attacking)
        {
            NewColor = FSlateColor(FLinearColor::Yellow);
        }
        else if (NewState == EPawnState::EPS_HitReaction)
        {
            NewColor = FSlateColor(FLinearColor(1.0f, 0.5f, 0.0f)); 
        }
        else
        {
            NewColor = FSlateColor(FLinearColor::White);
        }

        StateText->SetColorAndOpacity(NewColor);
    }

}
void UMainHUD::DisplayEnemyHealth(UAttributesComponent* EnemyAttributes)
{
    if (!EnemyAttributes || !EnemyHealthBar) return;

    if (LastEnemyAttributes)
    {
        LastEnemyAttributes->OnHealthChanged.RemoveDynamic(this, &UMainHUD::UpdateEnemyHealthBar);
    }

    LastEnemyAttributes = EnemyAttributes;
    LastEnemyAttributes->OnHealthChanged.AddDynamic(this, &UMainHUD::UpdateEnemyHealthBar);

    UpdateEnemyHealthBar(nullptr, EnemyAttributes->GetHealth(), 0.0f, EnemyAttributes->GetMaxHealth());

    EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);

    GetWorld()->GetTimerManager().SetTimer(HideEnemyBarTimerHandle, this, &UMainHUD::HideEnemyHealthBar, 3.0f, false);
}

void UMainHUD::UpdateEnemyHealthBar(UAttributesComponent* OwningComp, float Current, float Delta, float Max)
{
    if (EnemyHealthBar && Max > 0.0f)
    {
        float Percent = Current / Max;
        EnemyHealthBar->SetPercent(Percent);
    }
}

void UMainHUD::HideEnemyHealthBar()
{
    if (EnemyHealthBar)
    {
        EnemyHealthBar->SetVisibility(ESlateVisibility::Hidden);

        if (LastEnemyAttributes)
        {
            LastEnemyAttributes->OnHealthChanged.RemoveDynamic(this, &UMainHUD::UpdateEnemyHealthBar);
            LastEnemyAttributes = nullptr;
        }
    }
}