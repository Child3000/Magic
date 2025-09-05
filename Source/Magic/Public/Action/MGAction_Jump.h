// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGAction.h"
#include "MGAction_Jump.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MAGIC_API UMGAction_Jump : public UMGAction
{
	GENERATED_BODY()

public:
	UMGAction_Jump();
	
protected:
	virtual void ActionStarted_Implementation(AActor* Instigator) override;

	virtual void ActionStopped_Implementation(AActor* Instigator) override;
};
