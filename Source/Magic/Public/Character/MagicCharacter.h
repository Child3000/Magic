// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MagicCharacterBase.h"
#include "MagicCharacter.generated.h"

UCLASS()
class MAGIC_API AMagicCharacter : public AMagicCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMagicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
