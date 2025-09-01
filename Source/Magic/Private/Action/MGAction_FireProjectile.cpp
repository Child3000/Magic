// Copyright Bear Child


#include "Action/MGAction_FireProjectile.h"

#include "Character/MGCharacterBase.h"
#include "Projectile/MGProjectileBase.h"

UMGAction_FireProjectile::UMGAction_FireProjectile()
{
	ActionName = FName("Player.Ability.FireProjectile");
	SocketOfWeaponForProjectile = FName("Socket_Spawn_Projectile");
	DelayElapsedTimeSpawnProjectile = 0;
}

void UMGAction_FireProjectile::ActionStarted_Implementation(AActor* Instigator)
{
	Super::ActionStarted_Implementation(Instigator);

	if (!ensureAlways(ProjectileClass))
	{
		return;
	}
	if (!ensureAlways(Instigator))
	{
		return;
	}

	if (AMGCharacterBase* CB = Cast<AMGCharacterBase>(Instigator))
	{
		// play fire projectile animation.
		if (AnimMontage)
		{
			CB->PlayAnimMontage(AnimMontage);
		}

		// spawn projectile.
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("TimeElapsed_SpawnProjectile"), CB);
		GetWorld()->GetTimerManager().SetTimer(TimerHandleOfSpawnProjectile, TimerDelegate, DelayElapsedTimeSpawnProjectile, false);
	}
}	

void UMGAction_FireProjectile::TimeElapsed_SpawnProjectile(AMGCharacterBase* Instigator)
{
	if (!ensureAlways(ProjectileClass))
	{
		return;
	}
	if (!ensureAlways(Instigator))
	{
		return;
	}

	const FRotator CharacterRotation = Instigator->GetActorRotation();
	const auto* WeaponMesh = Instigator->GetWeaponMesh();
	
	FTransform  SpawnTransform;
	SpawnTransform.SetLocation(WeaponMesh->GetSocketLocation(SocketOfWeaponForProjectile));
	SpawnTransform.SetRotation(CharacterRotation.Quaternion());

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Instigator;
	SpawnParams.Owner = Instigator;
	
	GetWorld()->SpawnActor<AMGProjectileBase>(ProjectileClass, SpawnTransform, SpawnParams);

	StopAction(Instigator);;
}

void UMGAction_FireProjectile::ActionStopped_Implementation(AActor* Instigator)
{
	Super::ActionStopped_Implementation(Instigator);
}

