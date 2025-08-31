// Copyright Bear Child


#include "Action/MGActionComponent.h"

#include "Action/MGAction.h"


UMGActionComponent::UMGActionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMGActionComponent::AddAction(TSubclassOf<UMGAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}
	
	UMGAction* NewAction = NewObject<UMGAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UMGActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UMGAction* Action : Actions)
	{
		if (Action->ActionName == ActionName)
		{
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UMGActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UMGAction* Action : Actions)
	{
		if (Action->ActionName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;
}

