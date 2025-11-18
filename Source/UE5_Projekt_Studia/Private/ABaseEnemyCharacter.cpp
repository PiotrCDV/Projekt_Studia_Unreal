// Fill out your copyright notice in the Description page of Project Settings.

#include "ABaseEnemyCharacter.h"
#include "PickableWeapon.h"          
#include "AttributesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h" 
#include "TimerManager.h"          
AABaseEnemyCharacter::AABaseEnemyCharacter()
{
    AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComponent"));
    CurrentPawnState = EPawnState::EPS_Idle;
}

void AABaseEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (AttributesComponent)
    {
        AttributesComponent->OnDeath.AddDynamic(this, &AABaseEnemyCharacter::HandleDeath);
    }

    PlayerTarget = Cast<AABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (GetWorld() && PlayerTarget)
    {
        GetWorldTimerManager().SetTimer(
            AttackTimerHandle,
            this,
            &AABaseEnemyCharacter::CheckForPlayerAndAttack,
            0.5f,
            true
        );
    }
    if (DefaultWeaponClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        APickableWeapon* SpawnedWeapon = GetWorld()->SpawnActor<APickableWeapon>(DefaultWeaponClass, GetActorLocation(), GetActorRotation(), SpawnParams);

        if (SpawnedWeapon)
        {
            EquippedWeapon = SpawnedWeapon;

            EquippedWeapon->GetRootComponent()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);

            EquippedWeapon->SetActorEnableCollision(false);
        }
    }
}

void AABaseEnemyCharacter::CheckForPlayerAndAttack()
{
    if (!PlayerTarget || CurrentPawnState == EPawnState::EPS_Dead || CurrentPawnState == EPawnState::EPS_HitReaction)
    {
        return;
    }

    FVector TargetLocation = PlayerTarget->GetActorLocation();
    FVector SelfLocation = GetActorLocation();
    float Distance = FVector::Dist(SelfLocation, TargetLocation);

    if (CurrentPawnState != EPawnState::EPS_Attacking)
    {
        FVector Direction = (TargetLocation - SelfLocation);
        Direction.Z = 0.0f;
        Direction.Normalize();

        FRotator TargetRotation = Direction.Rotation();

        const float RotationSpeed = 10.0f; 
        FRotator NewRotation = FMath::RInterpTo(
            GetActorRotation(),
            TargetRotation,
            0.5f, 
            RotationSpeed
        );

        SetActorRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
    }


    if (Distance <= AttackRange)
    {
        if (CurrentPawnState != EPawnState::EPS_Attacking)
        {
            SetPawnState(EPawnState::EPS_InCombat);
            TryAttack();
        }
    }
    else
    {
        SetPawnState(EPawnState::EPS_Idle);
    }
}
void AABaseEnemyCharacter::SetPawnState(EPawnState NewState)
{
    CurrentPawnState = NewState;
}

void AABaseEnemyCharacter::TryAttack()
{
    if (CurrentPawnState != EPawnState::EPS_Idle && CurrentPawnState != EPawnState::EPS_InCombat)
    {
        return;
    }

    SetPawnState(EPawnState::EPS_Attacking);

    if (AttackMontage)
    {
        PlayAnimMontage(AttackMontage);


        if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
        {
            FOnMontageEnded EndedDelegate;
            EndedDelegate.BindUObject(this, &AABaseEnemyCharacter::OnMontageEnded);
            AnimInstance->Montage_SetEndDelegate(EndedDelegate, AttackMontage);
        }
    }
    else
    {
        AttackFinished();
    }
}

void AABaseEnemyCharacter::AttackFinished()
{
    if (CurrentPawnState == EPawnState::EPS_Attacking)
    {
        SetPawnState(EPawnState::EPS_InCombat);
    }
}

void AABaseEnemyCharacter::AttackCanceled()
{
    if (CurrentPawnState != EPawnState::EPS_Dead)
    {
        SetPawnState(EPawnState::EPS_InCombat);
    }
}

void AABaseEnemyCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    if (bInterrupted)
    {
        return;
    }

    if (Montage == AttackMontage)
    {
        AttackFinished();
    }
    else if (Montage == HitReactMontage)
    {
        if (CurrentPawnState != EPawnState::EPS_Dead)
        {
            SetPawnState(EPawnState::EPS_InCombat);
        }
    }
}


void AABaseEnemyCharacter::GetHit_Implementation(AActor* Attacker, float Damage)
{
    if (CurrentPawnState == EPawnState::EPS_Dead)
    {
        return;
    }

    if (CurrentPawnState == EPawnState::EPS_Attacking)
    {
        if (AttackMontage)
        {
            StopAnimMontage(AttackMontage);
        }
        AttackCanceled(); 
    }

    AttributesComponent->ApplyDamage(Damage);

    if (AttributesComponent->GetHealth() > 0.f)
    {
        SetPawnState(EPawnState::EPS_HitReaction);

        if (HitSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
        }
        if (HitReactMontage)
        {
            PlayAnimMontage(HitReactMontage);

            if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
            {
                FOnMontageEnded EndedDelegate;
                EndedDelegate.BindUObject(this, &AABaseEnemyCharacter::OnMontageEnded);
                AnimInstance->Montage_SetEndDelegate(EndedDelegate, HitReactMontage);
            }
        }
        else
        {
            SetPawnState(EPawnState::EPS_InCombat);
        }
    }
}

void AABaseEnemyCharacter::HandleDeath()
{
    GetWorldTimerManager().ClearTimer(AttackTimerHandle);
    StopAnimMontage();

    SetPawnState(EPawnState::EPS_Dead);

    GetCharacterMovement()->StopMovementImmediately();
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
}