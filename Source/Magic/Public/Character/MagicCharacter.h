// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MagicCharacterBase.h"
#include "MagicCharacter.generated.h"

class AMagicProjectileBase;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MAGIC_API AMagicCharacter : public AMagicCharacterBase
{
	GENERATED_BODY()

public:
	AMagicCharacter();

	void FireProjectile();
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditAnywhere, Category="Projectile")
	TSubclassOf<AMagicProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	FName WeaponProjectileSpawnSocketName;
};
