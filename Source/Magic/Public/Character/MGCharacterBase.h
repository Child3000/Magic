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

	/* Returns the mesh of weapon. */
	USkeletalMeshComponent* GetWeaponMesh() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName WeaponHandSocketName;
	
protected:
	virtual void BeginPlay() override;
};
