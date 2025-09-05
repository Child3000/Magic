// Copyright Bear Child


#include "Action/MGAction_Jump.h"

#include "GameFramework/Character.h"

UMGAction_Jump::UMGAction_Jump()
{
	ActionName = FName("Player.Ability.Jump");
}

void UMGAction_Jump::ActionStarted_Implementation(AActor* Instigator)
{
	Super::ActionStarted_Implementation(Instigator);

	if (ACharacter* Character = Cast<ACharacter>(Instigator))
	{
		Character->Jump();
	}
}

void UMGAction_Jump::ActionStopped_Implementation(AActor* Instigator)
{
	Super::ActionStopped_Implementation(Instigator);

	if (ACharacter* Character = Cast<ACharacter>(Instigator))
	{
		Character->StopJumping();
	}
}
