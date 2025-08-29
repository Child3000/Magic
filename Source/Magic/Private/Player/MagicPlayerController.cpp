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

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subsystem);
	subsystem->AddMappingContext(MagicContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Type::Default;
	
	FInputModeGameAndUI inputMode;
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);
}

void AMagicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto* enhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);
	enhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMagicPlayerController::OnInputMove);
}

void AMagicPlayerController::OnInputMove(const FInputActionValue& Value)
{
	const FVector2D moveInputAxis = Value.Get<FVector2D>();
	const FRotator controlRotation = GetControlRotation();
	const FRotator controlYawRotation = FRotator(0, controlRotation.Yaw, 0);

	const FVector forwardDirection = controlYawRotation.Vector();
	const FVector rightDirection = controlYawRotation.RotateVector(FVector::RightVector);

	if (APawn* pawnControlled = GetPawn())
	{
		pawnControlled->AddMovementInput(forwardDirection, moveInputAxis.X);
		pawnControlled->AddMovementInput(rightDirection, moveInputAxis.Y);
	}	
}
