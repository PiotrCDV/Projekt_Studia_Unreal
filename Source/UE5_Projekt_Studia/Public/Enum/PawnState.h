#pragma once


#include "CoreMinimal.h"

/**
 */
UENUM(BlueprintType)
enum class EPawnState : uint8
{
    EPS_Idle UMETA(DisplayName = "Idle"),

    EPS_InCombat UMETA(DisplayName = "InCombat"),

    EPS_HitReaction UMETA(DisplayName = "HitReaction"),

    EPS_Attacking UMETA(DisplayName = "Attacking"),

    EPS_Exhausted UMETA(DisplayName = "Exhausted"),

    EPS_Dead UMETA(DisplayName = "Dead")
};