// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MGAction.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MAGIC_API UMGAction : public UObject
{
	GENERATED_BODY()

public:
	/* An unique nickname to identify the action. */
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	/* Start the action from an instigator source. */
	void StartAction(AActor* Instigator);

	/* Stop the action from an instigator source. */
	void StopAction(AActor* Instigator);

protected:
	/* An implementable function in Blueprint to extend the behaviour of start action. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void BP_StartAction(AActor* Instigator);

	/* An implementable function in Blueprint to extend the behaviour of stop action. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void BP_StopAction(AActor* Instigator);
};
