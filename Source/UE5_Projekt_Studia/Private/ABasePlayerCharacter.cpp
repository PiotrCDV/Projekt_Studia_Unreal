// Fill out your copyright notice in the Description page of Project Settings.

#include "AttributesComponent.h"
#include "Widget/MainHUD.h" 
#include "Blueprint/UserWidget.h"
#include "ABasePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "InteractionComponent.h" 
#include "PickableWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"       
#include "Kismet/KismetSystemLibrary.h"  
#include "Engine/HitResult.h"            
#include "Engine/EngineTypes.h"          
#include "Math/Quat.h"                   
#include "Math/Color.h"           
#include "CombatInterface.h"
#include "InputMappingContext.h"

AABasePlayerCharacter::AABasePlayerCharacter()
{
    InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

    AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComponent"));

    PrimaryActorTick.bCanEverTick = true;
    bIsAttacking = false;

}

void AABasePlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MoveValue = Value.Get<FVector2D>();

    if (Controller && (MoveValue != FVector2D::ZeroVector))
    {
        if (MoveValue.X != 0.f)
        {
            const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
            const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
            AddMovementInput(Direction, MoveValue.X);
        }

        if (MoveValue.Y != 0.f)
        {
            const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);
            const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
            AddMovementInput(Direction, MoveValue.Y);
        }
    }
}

void AABasePlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bIsAttacking)
    {

        PerformAttackTrace();

    }
}

void AABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AABasePlayerCharacter::Move);
        EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AABasePlayerCharacter::Look);
        if (EquipAction)
        {
            EIC->BindAction(EquipAction, ETriggerEvent::Triggered, this, &AABasePlayerCharacter::Interact);
        }
        if (AttackAction)
        {
            EIC->BindAction(AttackAction, ETriggerEvent::Started, this, &AABasePlayerCharacter::Attack);
        }
    }
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (ULocalPlayer* LP = PC->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                if (MappingContext)
                {
                    Subsystem->AddMappingContext(MappingContext, 0);
                }
            }
        }
    }
}

void AABasePlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    InitializeHUD();
    SynchronizeHUD();
    if (APlayerController* PC = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            if (MappingContext)
            {
                Subsystem->AddMappingContext(MappingContext, 0);
            }
        }
    }


}

// Plik: AABasePlayerCharacter.cpp

// Plik: AABasePlayerCharacter.cpp

void AABasePlayerCharacter::SynchronizeHUD()
{
    // Log wejœcia do funkcji
    UE_LOG(LogTemp, Warning, TEXT("DEBUG: SynchronizeHUD - Funkcja wywolana."));

    if (UAttributesComponent* AttrComp = GetAttributesComponent())
    {
        // Log sprawdzenia wartoœci przed wys³aniem
        float CurrentHP = AttrComp->GetHealth();
        float MaxHP = AttrComp->GetMaxHealth();
        UE_LOG(LogTemp, Warning, TEXT("DEBUG: SynchronizeHUD - AttrComp znaleziony. Wysylam Broadcast. HP: %f / %f"), CurrentHP, MaxHP);

        // 1. Rêczne wywo³anie delegata Zdrowia
        AttrComp->OnHealthChanged.Broadcast(AttrComp, CurrentHP, 0.0f, MaxHP);

        // 2. Rêczne wywo³anie delegata Staminy
        AttrComp->OnStaminaChanged.Broadcast(AttrComp, AttrComp->GetStamina(), 0.0f, AttrComp->GetMaxStamina());
    }
    else
    {
        // Log b³êdu - brak komponentu
        UE_LOG(LogTemp, Error, TEXT("DEBUG: SynchronizeHUD - B£¥D! GetAttributesComponent() zwrocil NULL!"));
    }
}

void AABasePlayerCharacter::InitializeHUD()
{
    UE_LOG(LogTemp, Warning, TEXT("DEBUG: InitializeHUD - Funkcja wywolana."));

    // Sprawdzenie warunków wstêpnych
    if (PlayerHUDWidgetClass && IsPlayerControlled())
    {
        UE_LOG(LogTemp, Warning, TEXT("DEBUG: InitializeHUD - WidgetClass jest ustawiony i to jest Gracz. Tworze widget..."));

        // 1. STWÓRZ WID¯ET
        PlayerHUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

        if (PlayerHUDWidgetInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("DEBUG: InitializeHUD - Widget utworzony pomyslnie. Dodaje do Viewportu."));

            // 2. DODAJ DO VIEWPORTU
            PlayerHUDWidgetInstance->AddToViewport();

            // 3. POD£¥CZ DELEGATY:
            if (UAttributesComponent* AttrComp = GetAttributesComponent())
            {
                UE_LOG(LogTemp, Warning, TEXT("DEBUG: InitializeHUD - Podpinam delegaty (Bind)."));

                // Podpinamy funkcje Handle...Update do delegatów atrybutów.
                AttrComp->OnHealthChanged.AddDynamic(this, &AABasePlayerCharacter::HandleHealthUpdate);
                AttrComp->OnStaminaChanged.AddDynamic(this, &AABasePlayerCharacter::HandleStaminaUpdate);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("DEBUG: InitializeHUD - B£¥D! Nie znaleziono AttributesComponent przy probie podpiecia delegatow!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("DEBUG: InitializeHUD - B£¥D! CreateWidget zwrocil NULL (nie udalo sie stworzyc widgetu)."));
        }
    }
    else
    {
        if (!PlayerHUDWidgetClass) UE_LOG(LogTemp, Error, TEXT("DEBUG: InitializeHUD - B£¥D! PlayerHUDWidgetClass jest NULL (nie ustawiles BP w Details postac)!"));
        if (!IsPlayerControlled()) UE_LOG(LogTemp, Error, TEXT("DEBUG: InitializeHUD - Info: To nie jest postac sterowana przez gracza (IsPlayerControlled = false)."));
    }
}

/** * Implementacja: Wywo³ywana przez delegata UAttributesComponent::OnHealthChanged.
 * Przekazuje now¹ wartoœæ do paska w HUD.
 */
void AABasePlayerCharacter::HandleHealthUpdate(UAttributesComponent* OwningComp, float Current, float Delta, float Max)
{
    // 1. Rzutujemy generyczn¹ instancjê na nasz¹ klasê C++ UMainHUD.
    if (UMainHUD* HUDWidget = Cast<UMainHUD>(PlayerHUDWidgetInstance))
    {
        // 2. Wywo³ujemy natywn¹ funkcjê C++ w wid¿ecie, która zaktualizuje pasek.
        HUDWidget->UpdateHealth(Current, Max);
    }
}

/** * Implementacja: Wywo³ywana przez delegata UAttributesComponent::OnStaminaChanged.
 * Przekazuje now¹ wartoœæ do paska w HUD.
 */
void AABasePlayerCharacter::HandleStaminaUpdate(UAttributesComponent* OwningComp, float Current, float Delta, float Max)
{
    // 1. Rzutujemy generyczn¹ instancjê na nasz¹ klasê C++ UMainHUD.
    if (UMainHUD* HUDWidget = Cast<UMainHUD>(PlayerHUDWidgetInstance))
    {
        // 2. Wywo³ujemy natywn¹ funkcjê C++ w wid¿ecie, która zaktualizuje pasek.
        HUDWidget->UpdateStamina(Current, Max);
    }
}
void AABasePlayerCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D Look = Value.Get<FVector2D>();
    if (!Controller) return;

    AddControllerYawInput(Look.X);
    AddControllerPitchInput(-Look.Y);
}

void AABasePlayerCharacter::Equip(APickableWeapon* Weapon)
{
    if (!Weapon) return;

    CurrentWeapon = Weapon;

    FName SocketName = TEXT("WeaponSocket");

    if (USceneComponent* Grip = Weapon->GetGripPoint())
    {

        Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    }
    else
    {
        Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    }

    if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Weapon->GetRootComponent()))
    {
        PrimComp->SetSimulatePhysics(false);
        PrimComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

}

void AABasePlayerCharacter::Interact()
{
    if (InteractionComponent)
    {
        InteractionComponent->TryInteract(this);
    }
}


// Plik: AABasePlayerCharacter.cpp

void AABasePlayerCharacter::Attack(const FInputActionValue& Value)
{
    // ... (Twoje istniej¹ce warunki sprawdzaj¹ce blokady: bIsAttacking, CurrentWeapon, AnimMontage) ...
    if (bIsAttacking || !CurrentWeapon)
    {
        return;
    }
    if (GetMesh()->GetAnimInstance() && GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
    {
        return;
    }

    // --- LOGIKA KOSZTU STAMINY (PUNKT 3) ---
    if (UAttributesComponent* AttrComp = GetAttributesComponent())
    {
        float AttackCost = AttrComp->StaminaCosts.CostAttack;

        // TryConsumeStamina: sprawdza, czy mo¿na zap³aciæ, i jeœli tak, zu¿ywa staminê
        if (!AttrComp->TryConsumeStamina(AttackCost))
        {
            // Brak staminy, przerywamy akcjê
            return;
        }
    }

    // --- WYKONANIE AKCJI ---
    bIsAttacking = true;

    if (AttackMontage)
    {
        PlayAnimMontage(AttackMontage);

        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            FOnMontageEnded EndedDelegate;
            EndedDelegate.BindUObject(this, &AABasePlayerCharacter::OnAttackMontageEnded);
            AnimInstance->Montage_SetEndDelegate(EndedDelegate, AttackMontage);
        }
    }
    else
    {
        bIsAttacking = false;
    }
}

void AABasePlayerCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

    bIsAttacking = false;

}


void AABasePlayerCharacter::StartWeaponTrace()
{
    bIsAttacking = true;
    HitActors.Empty();
}

void AABasePlayerCharacter::EndWeaponTrace()
{
    bIsAttacking = false;
}

void AABasePlayerCharacter::PerformAttackTrace()
{
    if (!CurrentWeapon || !CurrentWeapon->GetHitbox())
    {
        return; 
    }

    UBoxComponent* Hitbox = CurrentWeapon->GetHitbox();

    FVector Start = Hitbox->GetComponentLocation();
    FVector End = Start; 
    FVector HalfSize = Hitbox->GetScaledBoxExtent();
    FRotator Orientation = Hitbox->GetComponentRotation();

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this); 
    ActorsToIgnore.Add(CurrentWeapon);

    FHitResult HitResult;

    bool bHit = UKismetSystemLibrary::BoxTraceSingle(
        GetWorld(),
        Start,
        End,
        HalfSize,
        Orientation,
        UEngineTypes::ConvertToTraceType(ECC_Visibility), 
        false,
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration, 
        HitResult,
        true,
        FLinearColor::Red,    
        FLinearColor::Green,  
        0.1f                  
    );
    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();

        if (!HitActors.Contains(HitActor))
        {
            HitActors.Add(HitActor);

            FVector HitLocation = HitResult.Location;


            if (HitActor->Implements<UCombatInterface>())
            {

                float DamageToDeal = CurrentWeapon->BaseDamage;

                ICombatInterface::Execute_GetHit(HitActor, this, DamageToDeal);

            }
        }
    }


}

