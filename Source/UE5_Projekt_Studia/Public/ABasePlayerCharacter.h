// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enum/PawnState.h" 
#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "ABasePlayerCharacter.generated.h"

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
    void SetPawnState(EPawnState NewState);

public:
    // Funkcja dostêpu (Get)
    UFUNCTION(BlueprintPure, Category = "State")
    FORCEINLINE EPawnState GetCurrentPawnState() const { return CurrentPawnState; }

protected:
    // **NOWE ZMIENNE HUD**
    // 1. Klasa HUD do u¿ycia w Blueprint (musi byæ UMainHUD dla ³atwego rzutowania)
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    TSubclassOf<class UMainHUD> PlayerHUDWidgetClass;

    // 2. Instancja wid¿etu (zawsze typu UUserWidget*, bo to zwraca CreateWidget)
    UPROPERTY()
    class UUserWidget* PlayerHUDWidgetInstance;

    /** Funkcja inicjuj¹ca HUD, wywo³ywana np. w BeginPlay */
    void InitializeHUD();
    void SynchronizeHUD();
    // **NOWE FUNKCJE DLA DELEGATÓW (CALLBACKS)**
    // 1. Funkcja wywo³ywana po zmianie Zdrowia
    UFUNCTION()
    void HandleHealthUpdate(UAttributesComponent* OwningComp, float Current, float Delta, float Max);

    // 2. Funkcja wywo³ywana po zmianie Staminy
    UFUNCTION()
    void HandleStaminaUpdate(UAttributesComponent* OwningComp, float Current, float Delta, float Max);

    // ... (pozosta³e funkcje)

protected:
    // W³aœciwoœæ komponentu (Zak³adamy, ¿e jest to w³aœciwoœæ Twojej klasy bazowej)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UAttributesComponent* AttributesComponent;

public:
    // Funkcja dostêpu, której brakuje kompilatorowi
    // Musi zwracaæ wskaŸnik do komponentu atrybutów.
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






