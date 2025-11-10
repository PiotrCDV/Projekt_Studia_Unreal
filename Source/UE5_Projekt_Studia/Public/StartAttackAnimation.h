// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "StartAttackAnimation.generated.h"

/**
 * 
 */
UCLASS()
class UE5_PROJEKT_STUDIA_API UStartAttackAnimation : public UAnimNotify
{
    GENERATED_BODY()

protected:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
