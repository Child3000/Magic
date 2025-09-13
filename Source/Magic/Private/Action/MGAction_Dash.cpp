// Copyright Bear Child


#include "Action/MGAction_Dash.h"

#include "Character/MGCharacter.h"

UMGAction_Dash::UMGAction_Dash()
{
	ActionName = "Player.Ability.Dash";

	DashMagnitude = 1000.0f;
}


void UMGAction_Dash::ActionStarted_Implementation(AActor* Instigator)
{
	Super::ActionStarted_Implementation(Instigator);

	UE_LOG(LogTemp, Log, TEXT("Dash !"));

	if (ACharacter* Character = Cast<AMGCharacter>(Instigator))
	{
		FVector DashDirection = Character->GetActorForwardVector();
		Character->LaunchCharacter(DashDirection * DashMagnitude, true, true);
	}

	StopAction(Instigator);
}


void UMGAction_Dash::ActionStopped_Implementation(AActor* Instigator)
{
	Super::ActionStopped_Implementation(Instigator);
}
