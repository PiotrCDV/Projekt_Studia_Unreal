#include "ABaseEnemyCharacter.h"
#include "PickableWeapon.h"           
#include "AttributesComponent.h"
#include "AI/EnemyAIController.h" // Do³¹czamy nag³ówek kontrolera
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h" 

AABaseEnemyCharacter::AABaseEnemyCharacter()
{
	AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComponent"));
	CurrentPawnState = EPawnState::EPS_Idle;
}

void AABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 1. Pobieramy nasz nowy kontroler AI
	AIController = Cast<AEnemyAIController>(GetController());

	if (AttributesComponent)
	{
		AttributesComponent->OnDeath.AddDynamic(this, &AABaseEnemyCharacter::HandleDeath);
		// 2. Podpinamy delegat wyczerpania staminy
		AttributesComponent->OnStaminaExhausted.AddDynamic(this, &AABaseEnemyCharacter::HandleStaminaExhausted);
	}

	// 3. Synchronizujemy stan pocz¹tkowy (Idle) z AI
	SyncPawnStateWithAI(CurrentPawnState);

	// 4. Spawnujemy broñ (bez zmian)
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

// G³ówna funkcja do zmiany stanu - aktualizuje i Pionka, i Blackboard AI
void AABaseEnemyCharacter::SyncPawnStateWithAI(EPawnState NewState)
{
	SetPawnState(NewState);
	if (AIController)
	{
		AIController->SetPawnStateInBlackboard(NewState);
	}
}

void AABaseEnemyCharacter::SetPawnState(EPawnState NewState)
{
	CurrentPawnState = NewState;
}

// Funkcja wywo³ywana, gdy skoñczy siê stamina
void AABaseEnemyCharacter::HandleStaminaExhausted()
{
	// Prze³¹czamy w stan Wyczerpania -> Behavior Tree zablokuje atakowanie
	SyncPawnStateWithAI(EPawnState::EPS_Exhausted);
}

// Funkcja wywo³ywana przez Behavior Tree Task "AttackPlayer"
void AABaseEnemyCharacter::StartAttackFromAI()
{
	// Atakuj tylko, jeœli nie jesteœ martwy ani trafiony
	if (CurrentPawnState != EPawnState::EPS_Dead && CurrentPawnState != EPawnState::EPS_HitReaction)
	{
		PlayAnimMontage(AttackMontage);
		// Uwaga: Stan "Attacking" jest ustawiany w samym Tasku BT, tutaj tylko odpalamy animacjê
	}
}

void AABaseEnemyCharacter::GetHit_Implementation(AActor* Attacker, float Damage)
{
	if (CurrentPawnState == EPawnState::EPS_Dead) return;

	// Jeœli dosta³ w trakcie ataku -> przerwij atak
	if (CurrentPawnState == EPawnState::EPS_Attacking)
	{
		if (AttackMontage) StopAnimMontage(AttackMontage);
	}

	// Zadaj obra¿enia
	AttributesComponent->ApplyDamage(Damage);

	if (AttributesComponent->GetHealth() > 0.f)
	{
		// Zmieñ stan na HitReaction (AI przestanie siê ruszaæ)
		SyncPawnStateWithAI(EPawnState::EPS_HitReaction);

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		if (HitReactMontage)
		{
			PlayAnimMontage(HitReactMontage);

			// Podpinamy delegat koñca animacji, ¿eby wiedzieæ kiedy wróciæ do walki
			if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
			{
				FOnMontageEnded EndedDelegate;
				EndedDelegate.BindUObject(this, &AABaseEnemyCharacter::OnMontageEnded);
				AnimInstance->Montage_SetEndDelegate(EndedDelegate, HitReactMontage);
			}
		}
		else
		{
			// Jak nie ma animacji, wracamy od razu
			SyncPawnStateWithAI(EPawnState::EPS_InCombat);
		}
	}
}

void AABaseEnemyCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bInterrupted) return; // Jeœli przerwano (np. œmierci¹), nie rób nic

	if (Montage == HitReactMontage)
	{
		if (CurrentPawnState != EPawnState::EPS_Dead)
		{
			// Koniec animacji trafienia -> wracamy do akcji
			// Sprawdzamy w AI czy mamy cel, ¿eby wiedzieæ czy InCombat czy Idle
			EPawnState NewState = EPawnState::EPS_Idle;
			if (AIController && AIController->GetBlackboardComponent() && AIController->GetBlackboardComponent()->GetValueAsObject(AIController->TargetActorKey))
			{
				NewState = EPawnState::EPS_InCombat;
			}
			SyncPawnStateWithAI(NewState);
		}
	}
	else if (Montage == AttackMontage)
	{
		// Koniec ataku -> wracamy do InCombat
		if (CurrentPawnState != EPawnState::EPS_Dead)
		{
			SyncPawnStateWithAI(EPawnState::EPS_InCombat);
		}
	}
}

void AABaseEnemyCharacter::HandleDeath()
{
	StopAnimMontage();

	// Ustaw stan na Martwy
	SyncPawnStateWithAI(EPawnState::EPS_Dead);

	// Poinformuj AI Controller (¿eby Behavior Tree przesta³o dzia³aæ)
	if (AIController)
	{
		AIController->SetIsDeadInBlackboard(true);
	}

	GetCharacterMovement()->StopMovementImmediately();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
}