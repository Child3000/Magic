// Copyright Bear Child


#include "Action/MGAction_Dash.h"

#include "Character/MGCharacter.h"
#include "Components/CapsuleComponent.h"

UMGAction_Dash::UMGAction_Dash()
{
	ActionName = "Player.Ability.Dash";
	
	DashMaxTravelDistance = 400.0f;
}


void UMGAction_Dash::ActionStarted_Implementation(AActor* Instigator)
{
	Super::ActionStarted_Implementation(Instigator);
	
	ACharacter* Character = Cast<AMGCharacter>(Instigator);
	if (!Character)
	{
		StopAction(Instigator);
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Dash !"));

	// collect trace's data.
	const FVector StartLocation = Character->GetActorLocation();
	const FVector DashDirection = Character->GetActorForwardVector();
	const FVector EndLocation = StartLocation + DashDirection * DashMaxTravelDistance;
	const FName ProfileName = UCollisionProfile::Pawn_ProfileName;
			
	// collect character's capsule data.
	float CapsuleRadius = 0;
	float CapsuleHalfHeight = 0;
	Character->GetCapsuleComponent()->GetScaledCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	// process capsule data.
	const float CapsuleDiameter = CapsuleRadius * 2;
	const int32 NumOfTraces = FMath::FloorToInt32(DashMaxTravelDistance / CapsuleDiameter) + 1;

	// collect collision params.
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);

	// track teleport location.
	FVector TeleportLocation = StartLocation;

	// capsule trace from end to start, until found first non-blocking hit with blocked ground hit.
	// which means, empty space in ground area.
	for (int32 i = 0; i < NumOfTraces; i++)
	{
		const FVector TraceLocation = StartLocation + DashDirection * (DashMaxTravelDistance - i * CapsuleDiameter);
			
		bool bHit = GetWorld()->OverlapBlockingTestByProfile(
			TraceLocation,
			FQuat::Identity,
			ProfileName,
			FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
			Params);

		FHitResult GroundHit;
		bool bGroundHit = GetWorld()->LineTraceSingleByProfile(
			GroundHit,
			TraceLocation,
			TraceLocation + FVector(0, 0, -1000),
			ProfileName,
			Params);
			
		DrawDebugCapsule(GetWorld(),
			TraceLocation,
			CapsuleHalfHeight, CapsuleRadius,
			FQuat::Identity,
			FColor::Green,
			false,
			2.0f);
			
		if (!bHit && bGroundHit)
		{
			TeleportLocation = TraceLocation;
			break;
		}
	}
	
	// teleport to location.
	Character->TeleportTo(TeleportLocation, Character->GetActorRotation());

	StopAction(Instigator);
}


void UMGAction_Dash::ActionStopped_Implementation(AActor* Instigator)
{
	Super::ActionStopped_Implementation(Instigator);
}
