#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

// Deklaracja delegata œmierci (OnDeath)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

// Nowy, szczegó³owy delegat do aktualizacji HUD (zdrowie i stamina)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChangedDelegate, UAttributesComponent*, OwningComp, float, NewValue, float, Delta, float, MaxValue);

// NOWY: Deklaracja delegata wywo³ywanego, gdy Stamina spadnie do 0
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaExhaustedDelegate);

// Nowa struktura do przechowywania kosztów akcji
USTRUCT(BlueprintType)
struct FStaminaCostStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina Costs")
    float CostAttack = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina Costs")
    float CostSprint = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina Costs")
    float CostJump = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina Costs")
    float StaminaRegenRate = 5.0f;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE5_PROJEKT_STUDIA_API UAttributesComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAttributesComponent();

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDeathDelegate OnDeath;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAttributeChangedDelegate OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAttributeChangedDelegate OnStaminaChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStaminaExhaustedDelegate OnStaminaExhausted;

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    void ApplyDamage(float Damage);

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    void SetHealth(float NewHealth);


    UFUNCTION(BlueprintCallable, Category = "Attributes")
    bool TryPayStaminaCost(float StaminaCost);

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    bool CanPayStaminaCost(float StaminaCost) const { return Stamina >= StaminaCost; }

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetStamina() const { return Stamina; }

    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetMaxStamina() const { return MaxStamina; }

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
    FStaminaCostStruct StaminaCosts;

protected:
    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
    float MaxStamina = 100.0f;

private:
    UPROPERTY(VisibleAnywhere, Category = "Attributes")
    float Health;

    UPROPERTY(VisibleAnywhere, Category = "Attributes")
    float Stamina;
};