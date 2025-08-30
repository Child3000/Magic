// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicCharacterBase.generated.h"

UCLASS(Abstract)
class MAGIC_API AMagicCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMagicCharacterBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	static const FName WeaponHandSocketName;
	
protected:
	virtual void BeginPlay() override;
};
