// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/MGInteractable.h"
#include "MGExplosiveBarrel.generated.h"

class UNiagaraSystem;
class URadialForceComponent;

UCLASS()
class MAGIC_API AMGExplosiveBarrel : public AActor, public IMGInteractable
{
	GENERATED_BODY()

public:
	AMGExplosiveBarrel();
	
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
	virtual void Interact(const FMGInteractorInfo& Info) override;
};
