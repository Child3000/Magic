// Copyright Bear Child


#include "Action/MGAction_Dash.h"

#include "Character/MGCharacter.h"
#include "Components/CapsuleComponent.h"

UMGAction_Dash::UMGAction_Dash()
{
	ActionName = "Player.Ability.Dash";
	
	DashMaxTravelDistance = 400.0f;

	DashTotalInterval = 0.5f;

	TickFlag = false;

	CurrentDashTime = 0.01f;

	DashMontageRate = 1;
}


void UMGAction_Dash::ActionStarted_Implementation(AActor* Instigator)
{
	Super::ActionStarted_Implementation(Instigator);

	if (!IsValid(Instigator))
	{
		StopAction(Instigator);
		return;
	}
	
	ACharacter* Character = Cast<AMGCharacter>(Instigator);
	if (!IsValid(Character))
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

	if (StartLocation == TeleportLocation)
	{
		StopAction(Character);
		return;
	}
	
	StartTick(FDashInterpolateInfo(StartLocation, TeleportLocation, Character));

	// // teleport to location.
	// Character->TeleportTo(TeleportLocation, Character->GetActorRotation());

	// StopAction(Instigator);
}

void UMGAction_Dash::ActionStopped_Implementation(AActor* Instigator)
{
	Super::ActionStopped_Implementation(Instigator);

	StopTick();
}



void UMGAction_Dash::StartTick(const FDashInterpolateInfo& Info)
{
	if (TickFlag == true)
	{
		return;
	}

	// set values.
	TickFlag = true;
	DashInfo = Info;

	// apply side effects on character.
	if (ACharacter* Character = DashInfo.Character.Get())
	{
		// ignore inputs while dashing.
		ApplyIgnoredInput(Character, true);

		// start anim montage with loop.
		StartPlayLoopDashMontage();
	}
}

void UMGAction_Dash::StopTick()
{
	if (TickFlag == false)
	{
		return;
	}

	// unapply side effects from character.
	if (ACharacter* Character = DashInfo.Character.Get())
	{
		// allow inputs after dashing.
		ApplyIgnoredInput(DashInfo.Character.Get(), false);
		
		// stop anim montage.
		StopPlayLoopDashMontage();
	}
	
	// reset values.
	TickFlag = false;
	DashInfo = FDashInterpolateInfo();
	CurrentDashTime = 0;
}


void UMGAction_Dash::ApplyIgnoredInput(ACharacter* Character, bool bIgnored)
{
	if (!IsValid(Character))
	{
		return;
	}
	
	if (AController* Controller = Character->GetController())
	{
		Controller->SetIgnoreMoveInput(bIgnored);
		Controller->SetIgnoreLookInput(bIgnored);
	}
}


// FTickableGameObject Begin
void UMGAction_Dash::Tick(float DeltaTime)
{
	ACharacter* Character = DashInfo.Character.Get();
	if (!Character)
	{
		StopAction(Character);
		return;
	}

	CurrentDashTime = FMath::Clamp(CurrentDashTime + DeltaTime, 0, DashTotalInterval);

	const float Alpha = CurrentDashTime / DashTotalInterval;

	const FVector Location = FMath::Lerp(DashInfo.StartLocation, DashInfo.EndLocation, Alpha);

	Character->SetActorLocation(Location);

	if (CurrentDashTime == DashTotalInterval)
	{
		StopAction(Character);
	}
}


ETickableTickType UMGAction_Dash::GetTickableTickType() const
{
	return ETickableTickType::Conditional;
}

bool UMGAction_Dash::IsTickable() const
{
	return TickFlag;
}

UWorld* UMGAction_Dash::GetTickableGameObjectWorld() const
{
	return GetWorld();
}

TStatId UMGAction_Dash::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMGAction_Dash, STATGROUP_Tickables);
}
// FTickableGameObject End

// Montage Begin

void UMGAction_Dash::StartPlayLoopDashMontage()
{
	if (!ensureAlways(DashMontage))
	{
		return;
	}

	const float AnimLength = DashMontage->GetPlayLength();
	
	if (GetWorld()->GetTimerManager().IsTimerActive(Timer_PlayLoopMontage) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(
			Timer_PlayLoopMontage,
			this,
			&UMGAction_Dash::PlayDashMontage,
			AnimLength,
			true,
			0
			);
	}
}

void UMGAction_Dash::StopPlayLoopDashMontage()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer_PlayLoopMontage);
	StopDashMontage();
}

void UMGAction_Dash::PlayDashMontage()
{
	ACharacter* Character = DashInfo.Character.Get();
	if (!Character)
	{
		return;
	}
	if (!ensureAlways(DashMontage))
	{
		return;
	}
	Character->PlayAnimMontage(DashMontage, DashMontageRate);

	GEngine->AddOnScreenDebugMessage(5, 0, FColor::Green, TEXT("PlayAnimation"));
}

void UMGAction_Dash::StopDashMontage()
{
	ACharacter* Character = DashInfo.Character.Get();
	if (!Character)
	{
		return;
	}
	if (!ensureAlways(DashMontage))
	{
		return;
	}
	Character->StopAnimMontage(DashMontage);
}

// Montage End
