// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGAction.h"
#include "MGAction_FireProjectile.generated.h"

class AMGProjectileBase;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MAGIC_API UMGAction_FireProjectile : public UMGAction
{
	GENERATED_BODY()

public:
	UMGAction_FireProjectile();
	
protected:
	virtual void ActionStarted_Implementation(AActor* Instigator) override;

	virtual void ActionStopped_Implementation(AActor* Instigator) override;

private:
	/* The projectile class to be spawned. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMGProjectileBase> ProjectileClass;

	/* The socket name of weapon to spawn the fire projectile. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	FName SocketOfWeaponForProjectile;

	/* The animation to be played to spawn the fire projectile. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> AnimMontage;

	/* The delay elapsed time in seconds before projectile is actually spawned. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true", ClampMin = "0.0", Units = "s"))
	float DelayElapsedTimeSpawnProjectile;

	/* Track the timer handle to delay spawn projectile. */
	FTimerHandle TimerHandleOfSpawnProjectile;

	UFUNCTION()
	void TimeElapsed_SpawnProjectile(AMGCharacterBase* Instigator);
};
