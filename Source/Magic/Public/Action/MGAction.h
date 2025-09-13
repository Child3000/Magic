// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "MGAction.generated.h"

class UMGActionComponent;

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

	/* Returns the owning component. */
	UMGActionComponent* GetOwningActionComponent() const;

protected:
	/* An implementable function in Blueprint to extend or override behaviour of start action.
	 * Keep ParentNode to extend native implementation; otherwise, override.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void ActionStarted(AActor* Instigator);

	/* An overrideable function in C++ to provide native implementation of start action. */
	virtual void ActionStarted_Implementation(AActor* Instigator);

	/* An implementable function in Blueprint to extend or override behaviour of stop action.
	 * Keep ParentNode to extend native implementation; otherwise, override.
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void ActionStopped(AActor* Instigator);

	/* An overrideable function in C++ to provide native implementation of stop action. */
	virtual void ActionStopped_Implementation(AActor* Instigator);


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	/* These tags are granted when activated, and removed when deactivated. */
	FGameplayTagContainer TagsGrantedDuringActivation;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	/* The activations don't happen when these tags are active. */
	FGameplayTagContainer TagsToBlockActivation;

};
