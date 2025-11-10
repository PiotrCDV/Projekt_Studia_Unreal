// Fill out your copyright notice in the Description page of Project Settings.


#include "EndAttackAnimation.h"
#include "ABasePlayerCharacter.h" 

void UEndAttackAnimation::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (AActor* Owner = MeshComp->GetOwner())
    {
        if (AABasePlayerCharacter* Character = Cast<AABasePlayerCharacter>(Owner))
        {

            Character->EndWeaponTrace();

        }
    }
}
