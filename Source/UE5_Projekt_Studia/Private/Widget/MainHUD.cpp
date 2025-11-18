// Fill out your copyright notice in the Description page of Project Settings.



#include "Widget/MainHUD.h"

// Do u¿ycia funkcji Cast<>, UMainHUD.h musi zawieraæ #include "Components/ProgressBar.h"

void UMainHUD::UpdateHealth(float Current, float Max)
{
    // Sprawdzamy, czy pasek HealthBar istnieje i czy Max jest wiêkszy od zera (unikamy dzielenia przez zero)
    if (HealthBar && Max > 0)
    {
        // ProgressBar.SetPercent() przyjmuje wartoœæ z zakresu [0.0, 1.0].
        // Obliczamy to poprzez dzielenie Current / Max.
        HealthBar->SetPercent(Current / Max);
    }
}

void UMainHUD::UpdateStamina(float Current, float Max)
{
    // Sprawdzamy, czy pasek StaminaBar istnieje i czy Max jest wiêkszy od zera
    if (StaminaBar && Max > 0)
    {
        // Obliczamy i ustawiamy procent paska staminy
        StaminaBar->SetPercent(Current / Max);
    }
}