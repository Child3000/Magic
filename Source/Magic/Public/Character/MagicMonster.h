// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "Character/MagicCharacterBase.h"
#include "MagicMonster.generated.h"

UCLASS()
class MAGIC_API AMagicMonster : public AMagicCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMagicMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
