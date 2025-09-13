// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGCharacter.h"
#include "MGMonster.generated.h"

class UMGObjectTagAsset;

UCLASS()
class MAGIC_API AMGMonster : public AMGCharacter
{
	GENERATED_BODY()

public:
	AMGMonster();

protected:
	virtual void BeginPlay() override;
	
protected:
	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	                    FVector NormalImpulse, const FHitResult& Hit);


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags")
	TObjectPtr<UMGObjectTagAsset> RespondToHitObjectTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags")
	TObjectPtr<UAnimMontage> BeingHitMontage;
};
