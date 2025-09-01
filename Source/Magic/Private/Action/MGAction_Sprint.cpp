// Copyright Bear Child


#include "Action/MGAction_Sprint.h"

#include "GameFramework/CharacterMovementComponent.h"

UMGAction_Sprint::UMGAction_Sprint()
{
	ActionName = FName("Player.Ability.Sprint");
	AddedSprintSpeed = 1000;
}

void UMGAction_Sprint::ActionStarted_Implementation(AActor* Instigator)
{
	Super::ActionStarted_Implementation(Instigator);

	if (!ensureAlways(Instigator))
	{
		return;
	}

	if (UCharacterMovementComponent* CMC = Instigator->GetComponentByClass<UCharacterMovementComponent>())
	{
		const float MaxWalkSpeed = CMC->MaxWalkSpeed;
		const float ResultMaxWalkSpeed = MaxWalkSpeed + FMath::Max(AddedSprintSpeed, 0);
		CMC->MaxWalkSpeed = ResultMaxWalkSpeed;
	}
}

void UMGAction_Sprint::ActionStopped_Implementation(AActor* Instigator)
{
	Super::ActionStopped_Implementation(Instigator);

	if (!ensureAlways(Instigator))
	{
		return;
	}

	if (UCharacterMovementComponent* CMC = Instigator->GetComponentByClass<UCharacterMovementComponent>())
	{
		const float MaxWalkSpeed = CMC->MaxWalkSpeed;
		const float ResultMaxWalkSpeed = MaxWalkSpeed - FMath::Max(AddedSprintSpeed, 0);
		CMC->MaxWalkSpeed = ResultMaxWalkSpeed;
	}
}
