// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGCharacterBase.h"
#include "MGCharacter.generated.h"

class AMGProjectileBase;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MAGIC_API AMGCharacter : public AMGCharacterBase
{
	GENERATED_BODY()

public:
	AMGCharacter();

	void FireProjectile();
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditAnywhere, Category="Projectile")
	TSubclassOf<AMGProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	FName WeaponProjectileSpawnSocketName;
};
