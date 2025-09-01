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

	/* Add new action instances. */
	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddActions(TArray<TSubclassOf<UMGAction>> ActionClasses);

	/* Start the first found action instance. Returns true if action started; otherwise, false. */
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	/* Stop the first found action instance. Returns true if action stopped; otherwise, false. */
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StopActionByName(AActor* Instigator,FName ActionName);

protected:
	/* The default actions that are allowed to do. */
	UPROPERTY(EditDefaultsOnly, Category = "Action", meta = (AllowAbstract = "false", BlueprintBaseOnly = "true"))
	TArray<TSubclassOf<UMGAction>> DefaultGrantedActions;
	
	/* A list of actions that are allowed to do at the moment. */
	UPROPERTY()
	TArray<TObjectPtr<UMGAction>> Actions;
	
	virtual void BeginPlay() override;
};
