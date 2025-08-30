// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicProjectileBase.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class MAGIC_API AMagicProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AMagicProjectileBase();
protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
private:
	UPROPERTY(VisibleAnywhere, Category="Magic|Component")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere, Category="Magic|Component")
	TObjectPtr<UProjectileMovementComponent> ProjectileComp;

	UPROPERTY(VisibleAnywhere, Category="Magic|Effect")
	TObjectPtr<UNiagaraComponent> NiagaraComp;

	UPROPERTY(EditAnywhere, Category="Magic|Effect")
	TObjectPtr<UNiagaraSystem> ExplodedEffect;

	UFUNCTION()
	void ProjectileHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
};
