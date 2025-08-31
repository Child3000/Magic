// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MGActionComponent.generated.h"


class UMGAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGIC_API UMGActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMGActionComponent();

	/* Add new action instance. */
	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddAction(TSubclassOf<UMGAction> ActionClass);

	/* Start the first found action instance. Returns true if action started; otherwise, false. */
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	/* Stop the first found action instance. Returns true if action stopped; otherwise, false. */
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StopActionByName(AActor* Instigator,FName ActionName);

protected:
	/* A list of actions that are allowed to do at the moment. */
	UPROPERTY()
	TArray<TObjectPtr<UMGAction>> Actions;
};
