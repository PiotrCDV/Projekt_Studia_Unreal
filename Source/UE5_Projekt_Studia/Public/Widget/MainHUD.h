
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MainHUD.generated.h"

/**
 * Klasa HUD obs³uguj¹ca pasek ¿ycia i staminy
 */
UCLASS()
class UE5_PROJEKT_STUDIA_API UMainHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    // Funkcje aktualizuj¹ce paski (Punkt 2.3)
    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdateHealth(float Current, float Max);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdateStamina(float Current, float Max);

protected:
    // Zmienne do powi¹zania z elementami ProgressBar w Blueprint (WBP_MainHUD)
    // UWAGA: Nazwy musz¹ siê zgadzaæ z nazwami elementów w Blueprint!
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* StaminaBar;
};