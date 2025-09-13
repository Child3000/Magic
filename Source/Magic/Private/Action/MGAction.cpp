// Copyright Bear Child


#include "Action/MGAction.h"

#include "Action/MGActionComponent.h"

void UMGAction::StartAction(AActor* Instigator)
{
	UMGActionComponent* ActionComp = GetOwningActionComponent();
	
	// ignore blocked tags.
	if (ActionComp->GetActiveGameplayTag().HasAny(TagsToBlockActivation))
	{
		UE_LOG(LogTemp, Log, TEXT("Blocked %s"), *GetNameSafe(this));
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Running %s"), *GetNameSafe(this));

	// add granted tags.
	ActionComp->AddActiveGameplayTag(TagsGrantedDuringActivation);
	
	ActionStarted(Instigator);
}

void UMGAction::StopAction(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped %s"), *GetNameSafe(this));

	// remove granted tags.
	UMGActionComponent* ActionComp = GetOwningActionComponent();
	ActionComp->RemoveActiveGameplayTag(TagsGrantedDuringActivation);
	
	ActionStopped(Instigator);
}

UMGActionComponent* UMGAction::GetOwningActionComponent() const
{
	return CastChecked<UMGActionComponent>(GetOuter());
}

void UMGAction::ActionStarted_Implementation(AActor* Instigator)
{
}

void UMGAction::ActionStopped_Implementation(AActor* Instigator)
{
}
