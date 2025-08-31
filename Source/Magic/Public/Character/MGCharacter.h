// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGCharacterBase.h"
#include "MGCharacter.generated.h"

class UMGActionComponent;
class AMGProjectileBase;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MAGIC_API AMGCharacter : public AMGCharacterBase
{
	GENERATED_BODY()

public:
	AMGCharacter();

	void StartFireProjectile();

	void StartSprint();

	void StopSprint();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UMGActionComponent> ActionComp;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AMGProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FName WeaponProjectileSpawnSocketName;
};
