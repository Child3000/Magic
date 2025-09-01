// Copyright Bear Child


#include "Action/MGAction.h"

void UMGAction::StartAction(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running %s"), *GetNameSafe(this));
	ActionStarted(Instigator);
}

void UMGAction::StopAction(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped %s"), *GetNameSafe(this));
	ActionStopped(Instigator);
}

void UMGAction::ActionStarted_Implementation(AActor* Instigator)
{
}

void UMGAction::ActionStopped_Implementation(AActor* Instigator)
{
}
