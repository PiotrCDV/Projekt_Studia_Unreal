// Plik: UMainHUD.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MainHUD.generated.h"

class UTextBlock; // Dodajemy forward declaration dla UTextBlock
enum class EPawnState : uint8; // Forward declaration dla EPawnState

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

    // --- DODANE DLA PUNKTU 5 (TEKST STANU) ---
    UFUNCTION()
    void HandlePawnStateUpdate(EPawnState NewState);

protected:
    // Zmienne do powi¹zania z elementami ProgressBar w Blueprint (WBP_MainHUD)
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* StaminaBar;

    // --- NOWA ZMIENNA DLA TEKSTU STANU ---
    // Musisz nazwaæ go 'StateText' w UMG i zaznaczyæ 'Is Variable'
    UPROPERTY(meta = (BindWidget))
    UTextBlock* StateText;

private:
    // Prywatna funkcja pomocnicza do konwersji Enum na FString
    FString GetPawnStateString(EPawnState State) const;
};