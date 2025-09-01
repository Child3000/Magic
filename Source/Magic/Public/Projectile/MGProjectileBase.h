// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGProjectileBase.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class MAGIC_API AMGProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AMGProjectileBase();
	
protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
private:
	UPROPERTY(VisibleAnywhere, Category="Projectile")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere, Category="Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileComp;

	UPROPERTY(VisibleAnywhere, Category="Projectile")
	TObjectPtr<UNiagaraComponent> NiagaraComp;

	UPROPERTY(EditAnywhere, Category="Projectile")
	TObjectPtr<UNiagaraSystem> ExplodedEffect;

	UFUNCTION()
	void ProjectileHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
};
