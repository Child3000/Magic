// Copyright Bear Child


#include "Player/MGPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/MGCharacter.h"
#include "Kismet/GameplayStatics.h"

AMGPlayerController::AMGPlayerController()
{
	bReplicates = false;
}

void AMGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(MagicContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(MagicContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Type::Default;
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AMGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMGPlayerController::InputMove);
	EnhancedInput->BindAction(FireAction, ETriggerEvent::Started, this, &AMGPlayerController::InputFire);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &AMGPlayerController::InputStartSprint);
	EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &AMGPlayerController::InputStopSprint);
}

void AMGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AMGPlayerController::CursorTrace()
{
	FHitResult HitResult;
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	GetHitResultUnderCursorByChannel(TraceType, false, HitResult);

	const bool bHit = HitResult.bBlockingHit;
	if (bHit && HitResult.GetActor() &&
		Cast<IMGInteractGuide>(HitResult.GetActor()))
	{
		if (CurrentGuide != HitResult.GetActor())
		{
			// hide previous guide if any.
			if (IsValid(CurrentGuide.GetObject()))
				CurrentGuide->OnHideInteractGuide();
			
			// show current guide.
			CurrentGuide = HitResult.GetActor();
			CurrentGuide->OnShowInteractGuide();
		}
	}
	else
	{
		// hide guide.
		if (IsValid(CurrentGuide.GetObject()))
		{
			CurrentGuide->OnHideInteractGuide();
			CurrentGuide = nullptr;
		}
	}
}

void AMGPlayerController::InputMove(const FInputActionValue& Value)
{
	const FVector2D InputAxis = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

	const FVector ForwardDir = YawRotation.Vector();
	const FVector RightDir = YawRotation.RotateVector(FVector::RightVector);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDir, InputAxis.X);
		ControlledPawn->AddMovementInput(RightDir, InputAxis.Y);
	}	
}

void AMGPlayerController::InputFire(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		if (AMGCharacter* MC = CastChecked<AMGCharacter>(ControlledPawn))
		{
			MC->StartFireProjectile();
		}
	}
}

void AMGPlayerController::InputStartSprint(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		if (AMGCharacter* MC = CastChecked<AMGCharacter>(ControlledPawn))
		{
			MC->StartSprint();
		}
	}
}

void AMGPlayerController::InputStopSprint(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		if (AMGCharacter* MC = CastChecked<AMGCharacter>(ControlledPawn))
		{
			MC->StopSprint();
		}
	}
}
