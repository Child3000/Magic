// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGExplosiveBarrel.generated.h"

class UNiagaraSystem;
class URadialForceComponent;

UCLASS()
class MAGIC_API AMGExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	AMGExplosiveBarrel();

protected:
	virtual void BeginPlay() override;
	
protected:
	#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ExplosiveBarrel")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ExplosiveBarrel")
	TObjectPtr<URadialForceComponent> RadialForceComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ExplosiveBarrel")
	TObjectPtr<UNiagaraSystem> ExplodeEffect;

	#pragma endregion Components

protected:
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	                    FVector NormalImpulse, const FHitResult& Hit);
};
