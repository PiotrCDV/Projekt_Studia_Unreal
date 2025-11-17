// Fill out your copyright notice in the Description page of Project Settings.

#include "ABaseEnemyCharacter.h"
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
}

void AABaseEnemyCharacter::CheckForPlayerAndAttack()
{
    if (!PlayerTarget || CurrentPawnState == EPawnState::EPS_Dead || CurrentPawnState == EPawnState::EPS_HitReaction)
    {
        return;
    }

    float Distance = FVector::Dist(GetActorLocation(), PlayerTarget->GetActorLocation());

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