// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGAction.h"
#include "MGAction_Sprint.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MAGIC_API UMGAction_Sprint : public UMGAction
{
	GENERATED_BODY()

public:
	UMGAction_Sprint();

	/* Speed added when sprint started. The value must be positive number. */
	UPROPERTY(EditAnywhere, Category = "Sprint", meta = (ClampMin = "0.0", Units = "cm/s"))
	float AddedSprintSpeed;
	
	virtual void ActionStarted_Implementation(AActor* Instigator) override;

	virtual void ActionStopped_Implementation(AActor* Instigator) override;
};
