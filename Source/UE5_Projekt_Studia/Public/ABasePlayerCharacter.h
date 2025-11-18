// Plik: AABasePlayerCharacter.h

#pragma once

#include "Enum/PawnState.h"
#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "ABasePlayerCharacter.generated.h"

// --- DODANE DLA PUNKTU 5 (KOMUNIKACJA HUD) ---
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnStateChanged, EPawnState, NewState);
// ----------------------------------------------

class UMainHUD;
class UAttributesComponent;
class UInputAction;
class UInputMappingContext;
class UInteractionComponent;
class UAnimMontage;
class APickableWeapon;
struct FInputActionValue;

UCLASS()
class UE5_PROJEKT_STUDIA_API AABasePlayerCharacter : public AABaseCharacter
{
    GENERATED_BODY()

public:
    AABasePlayerCharacter();

    void StartWeaponTrace();
    void EndWeaponTrace();

public:
    // Zmienna przechowuj¹ca aktualny stan
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    EPawnState CurrentPawnState = EPawnState::EPS_Idle;

    // Funkcja do zmiany stanu (dostêpna z Blueprint)
    UFUNCTION(BlueprintCallable, Category = "State")
    virtual void SetPawnState(EPawnState NewState); // Usuniêto 'override' jeœli brak w AABaseCharacter

public:
    // Funkcja dostêpu (Get)
    UFUNCTION(BlueprintPure, Category = "State")
    FORCEINLINE EPawnState GetCurrentPawnState() const { return CurrentPawnState; }

    // --- DODANE DLA PUNKTU 5 (DELEGAT STANU) ---
    UPROPERTY(BlueprintAssignable, Category = "Events|State")
    FOnPawnStateChanged OnPawnStateChanged;
    // ---------------------------------------------


protected:
    // **NOWE ZMIENNE HUD**
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    TSubclassOf<class UMainHUD> PlayerHUDWidgetClass;

    UPROPERTY()
    class UUserWidget* PlayerHUDWidgetInstance;

    void InitializeHUD();
    void SynchronizeHUD();

    // **NOWE FUNKCJE DLA DELEGATÓW (CALLBACKS)**
    UFUNCTION()
    void HandleHealthUpdate(UAttributesComponent* OwningComp, float Current, float Delta, float Max);

    UFUNCTION()
    void HandleStaminaUpdate(UAttributesComponent* OwningComp, float Current, float Delta, float Max);



private:
    // Zmienna stanu sprintu
    bool bIsSprinting = false;

protected:
    // W³aœciwoœæ komponentu
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UAttributesComponent* AttributesComponent;

public:
    // Funkcja dostêpu (FIX B£ÊDU E0020)
    FORCEINLINE UAttributesComponent* GetAttributesComponent() const { return AttributesComponent; }

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* MappingContext;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
    UInputAction* MoveAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
    UInputAction* EquipAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
    UInputAction* AttackAction;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    // --- DODANE AKCJE DLA PUNKTU 3/4 ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
    UInputAction* SprintAction;
    // -----------------------------------

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
    UInteractionComponent* InteractionComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    APickableWeapon* CurrentWeapon;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
    UAnimMontage* AttackMontage;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void Move(const FInputActionValue& Value);
    virtual void BeginPlay() override;
    void Look(const FInputActionValue& Value);
    virtual void Equip(APickableWeapon* Weapon);
    void Interact();
    void Attack(const FInputActionValue& Value);


protected:
    void PerformAttackTrace();


private:
    bool bIsAttacking;

    UPROPERTY()
    TArray<AActor*> HitActors;

protected:

    void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};