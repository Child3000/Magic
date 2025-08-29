// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MagicCharacterBase.h"
#include "MagicCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MAGIC_API AMagicCharacter : public AMagicCharacterBase
{
	GENERATED_BODY()

public:
	AMagicCharacter();
protected:
	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category="Component")
	TObjectPtr<UCameraComponent> CameraComp;
};
