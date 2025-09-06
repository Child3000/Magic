// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MGInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGIC_API UMGInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/* The radius of trace detection. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float Radius;

	/* When flagged, ignore detecting owning actor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	uint32 bIgnoreOwningActor:1;
	
protected:
	UMGInteractionComponent();
	
	virtual void BeginPlay() override;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void UpdateCollisionObjectQueryParams();

public:
	void AddCollisionChannelToAffect(enum ECollisionChannel CollisionChannel);
	
	void AddObjectTypeToAffect(TEnumAsByte<enum EObjectTypeQuery> ObjectType);
	
	void RemoveObjectTypeToAffect(TEnumAsByte<enum EObjectTypeQuery> ObjectType);

protected:
	/** The object types that are detected by this interaction component */
	UPROPERTY(EditAnywhere, Category = "Interaction")
	TArray<TEnumAsByte<enum EObjectTypeQuery> > ObjectTypesToAffect;

	/** Cached object query params derived from ObjectTypesToAffect */
	FCollisionObjectQueryParams CollisionObjectQueryParams;
};
