// Plik: UMainHUD.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "AttributesComponent.h" 
#include "MainHUD.generated.h"

class UTextBlock; // Dodajemy forward declaration dla UTextBlock
enum class EPawnState : uint8; // Forward declaration dla EPawnState


UCLASS()
class UE5_PROJEKT_STUDIA_API UMainHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdateHealth(float Current, float Max);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void UpdateStamina(float Current, float Max);

    void DisplayEnemyHealth(UAttributesComponent* EnemyAttributes);

    UFUNCTION()
    void HandlePawnStateUpdate(EPawnState NewState);

protected:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* StaminaBar;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* EnemyHealthBar;

    UFUNCTION()
    void UpdateEnemyHealthBar(UAttributesComponent* OwningComp, float Current, float Delta, float Max);

    UFUNCTION()
    void HideEnemyHealthBar();


    UPROPERTY(meta = (BindWidget))
    UTextBlock* StateText;

private:
    FString GetPawnStateString(EPawnState State) const;

    FTimerHandle HideEnemyBarTimerHandle;

    UPROPERTY()
    UAttributesComponent* LastEnemyAttributes;
};