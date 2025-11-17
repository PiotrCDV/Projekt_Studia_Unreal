// Fill out your copyright notice in the Description page of Project Settings.



#include "ABaseEnemyCharacter.h"
#include "AttributesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

AABaseEnemyCharacter::AABaseEnemyCharacter()
{
    AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComponent"));
}

void AABaseEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (AttributesComponent)
    {
        AttributesComponent->OnDeath.AddDynamic(this, &AABaseEnemyCharacter::HandleDeath);
    }
}

void AABaseEnemyCharacter::GetHit_Implementation(AActor* Attacker, float Damage)
{
    if (AttributesComponent->GetHealth() <= 0.f)
    {
        return;
    }

    AttributesComponent->ApplyDamage(Damage);

    if (AttributesComponent->GetHealth() > 0.f)
    {
        if (HitSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
        }
        if (HitReactMontage)
        {
            PlayAnimMontage(HitReactMontage);
        }
    }
}

void AABaseEnemyCharacter::HandleDeath()
{

    GetCharacterMovement()->StopMovementImmediately();
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetMesh()->SetSimulatePhysics(true);
    GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
}