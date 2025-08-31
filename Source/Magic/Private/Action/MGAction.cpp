// Copyright Bear Child


#include "Action/MGAction.h"

void UMGAction::StartAction(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running %s"), *GetNameSafe(this));
	BP_StartAction(Instigator);
}

void UMGAction::StopAction(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped %s"), *GetNameSafe(this));
	BP_StopAction(Instigator);
}
