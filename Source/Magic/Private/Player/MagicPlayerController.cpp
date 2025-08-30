// Copyright Bear Child


#include "Player/MagicPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMagicPlayerController::AMagicPlayerController()
{
	bReplicates = false;
}

void AMagicPlayerController::BeginPlay()
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

void AMagicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMagicPlayerController::InputMove);
}

void AMagicPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AMagicPlayerController::CursorTrace()
{
	FHitResult HitResult;
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	GetHitResultUnderCursorByChannel(TraceType, false, HitResult);

	const bool bHit = HitResult.bBlockingHit;
	if (bHit && HitResult.GetActor() &&
		Cast<IMagicInteractGuide>(HitResult.GetActor()))
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

void AMagicPlayerController::InputMove(const FInputActionValue& Value)
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