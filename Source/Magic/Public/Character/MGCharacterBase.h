// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MGCharacterBase.generated.h"

UCLASS(Abstract)
class MAGIC_API AMGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMGCharacterBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	static const FName WeaponHandSocketName;
	
protected:
	virtual void BeginPlay() override;
};
