// Fill out your copyright notice in the Description page of Project Settings.

#include "Enum/PawnState.h"
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



void AABasePlayerCharacter::SynchronizeHUD()
{

    if (UAttributesComponent* AttrComp = GetAttributesComponent())
    {
        float CurrentHP = AttrComp->GetHealth();
        float MaxHP = AttrComp->GetMaxHealth();

        AttrComp->OnHealthChanged.Broadcast(AttrComp, CurrentHP, 0.0f, MaxHP);

        AttrComp->OnStaminaChanged.Broadcast(AttrComp, AttrComp->GetStamina(), 0.0f, AttrComp->GetMaxStamina());
    }
    else
    {
    }
}


void AABasePlayerCharacter::InitializeHUD()
{
    if (!PlayerHUDWidgetClass || !IsPlayerControlled())
    {
        return;
    }

    PlayerHUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);

    if (PlayerHUDWidgetInstance)
    {
        PlayerHUDWidgetInstance->AddToViewport();

        if (UAttributesComponent* AttrComp = GetAttributesComponent())
        {
            AttrComp->OnHealthChanged.AddDynamic(this, &AABasePlayerCharacter::HandleHealthUpdate);
            AttrComp->OnStaminaChanged.AddDynamic(this, &AABasePlayerCharacter::HandleStaminaUpdate);

            if (UMainHUD* HUDWidget = Cast<UMainHUD>(PlayerHUDWidgetInstance))
            {
                OnPawnStateChanged.AddDynamic(HUDWidget, &UMainHUD::HandlePawnStateUpdate);
            }

            AttrComp->OnHealthChanged.Broadcast(AttrComp, AttrComp->GetHealth(), 0.0f, AttrComp->GetMaxHealth());
            AttrComp->OnStaminaChanged.Broadcast(AttrComp, AttrComp->GetStamina(), 0.0f, AttrComp->GetMaxStamina());

            OnPawnStateChanged.Broadcast(GetCurrentPawnState());
        }
        else
        {
        }
    }
}


void AABasePlayerCharacter::HandleHealthUpdate(UAttributesComponent* OwningComp, float Current, float Delta, float Max)
{
    if (UMainHUD* HUDWidget = Cast<UMainHUD>(PlayerHUDWidgetInstance))
    {
        HUDWidget->UpdateHealth(Current, Max);
    }
}


void AABasePlayerCharacter::HandleStaminaUpdate(UAttributesComponent* OwningComp, float Current, float Delta, float Max)
{
    if (UMainHUD* HUDWidget = Cast<UMainHUD>(PlayerHUDWidgetInstance))
    {
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


void AABasePlayerCharacter::SetPawnState(EPawnState NewState)
{
    if (CurrentPawnState != NewState)
    {
        CurrentPawnState = NewState;

        OnPawnStateChanged.Broadcast(NewState); 

        if (UCharacterMovementComponent* Movement = GetCharacterMovement())
        {
            if (NewState == EPawnState::EPS_Exhausted)
            {
                Movement->MaxWalkSpeed = 100.0f;
            }
            else 
            {
                Movement->MaxWalkSpeed = 600.0f; 
            }
        }
    }
}
void AABasePlayerCharacter::Interact()
{
    if (InteractionComponent)
    {
        InteractionComponent->TryInteract(this);
    }
}



void AABasePlayerCharacter::Attack(const FInputActionValue& Value)
{
    if (bIsAttacking || !CurrentWeapon)
    {
        return;
    }
    if (GetMesh()->GetAnimInstance() && GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
    {
        return;
    }

    if (UAttributesComponent* AttrComp = GetAttributesComponent())
    {
        float AttackCost = AttrComp->StaminaCosts.CostAttack;

        if (!AttrComp->TryPayStaminaCost(AttackCost))
        {
            return;
        }
    }

    bIsAttacking = true;

    SetPawnState(EPawnState::EPS_Attacking);

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
        SetPawnState(EPawnState::EPS_Idle);
    }
}

void AABasePlayerCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    bIsAttacking = false;

    SetPawnState(EPawnState::EPS_Idle);
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

            if (HitActor->Implements<UCombatInterface>())
            {
                float DamageToDeal = CurrentWeapon->BaseDamage;
                ICombatInterface::Execute_GetHit(HitActor, this, DamageToDeal);
            }

            if (UAttributesComponent* EnemyAttributes = HitActor->FindComponentByClass<UAttributesComponent>())
            {
                if (PlayerHUDWidgetInstance)
                {
                    if (UMainHUD* MyHUD = Cast<UMainHUD>(PlayerHUDWidgetInstance))
                    {
                        MyHUD->DisplayEnemyHealth(EnemyAttributes);
                    }
                }
            }
        }
    }
}
