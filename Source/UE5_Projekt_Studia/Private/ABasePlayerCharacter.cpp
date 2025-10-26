// Fill out your copyright notice in the Description page of Project Settings.


#include "ABasePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "InteractionComponent.h" // Upewnij siê, ¿e jest dodany
#include "PickableWeapon.h"
#include "Components/SkeletalMeshComponent.h"

AABasePlayerCharacter::AABasePlayerCharacter()
{
    InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

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

void AABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AABasePlayerCharacter::Move);
        EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AABasePlayerCharacter::Look);
    }
}

void AABasePlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

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

    // Ustaw referencjê do aktualnej broni
    CurrentWeapon = Weapon;

    // Podepnij broñ do socketu na mesh'u postaci
    FName SocketName = TEXT("WeaponSocket");
    Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

    UE_LOG(LogTemp, Warning, TEXT("Gracz wyposa¿y³ broñ: %s"), *Weapon->GetName());
}

