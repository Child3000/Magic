// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGAction.h"
#include "MGAction_Dash.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MAGIC_API UMGAction_Dash : public UMGAction
{
	GENERATED_BODY()

public:
	UMGAction_Dash();

protected:
	virtual void ActionStarted_Implementation(AActor* Instigator) override;

	virtual void ActionStopped_Implementation(AActor* Instigator) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Action", meta=(AllowPrivateAccess=true))
	float DashMagnitude;
};
