// Copyright Bear Child


#include "Character/MGCharacter.h"

#include "Action/MGActionComponent.h"
#include "Attributes/MGAttributeComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/MGInteractionComponent.h"
#include "UI/MGPlayerWidget.h"

AMGCharacter::AMGCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 650;
	SpringArmComp->SetRelativeRotation(FRotator(-45, 0, 0));
	SpringArmComp->bUsePawnControlRotation = false;
	// fixed camera regardless of character rotation.
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritYaw = false;
	SpringArmComp->bInheritRoll = false;
	SpringArmComp->bDoCollisionTest = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	ActionComp = CreateDefaultSubobject<UMGActionComponent>("ActionComp");
	InteractionComp = CreateDefaultSubobject<UMGInteractionComponent>("InteractionComp");
	InteractionComp->SetAutoActivate(true);
	AttributeComp = CreateDefaultSubobject<UMGAttributeComponent>("AttributeComp");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->GravityScale = 1.2;
	GetCharacterMovement()->JumpZVelocity = 600;
	GetCharacterMovement()->AirControl = 1.0;
}


void AMGCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled() && PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UMGPlayerWidget>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
		}
	}
}

void AMGCharacter::StartJump()
{
	ActionComp->StartActionByName(this, FName("Player.Ability.Jump"));
}

void AMGCharacter::StopJump()
{
	ActionComp->StopActionByName(this, FName("Player.Ability.Jump"));
}

void AMGCharacter::Dash()
{
	ActionComp->StartActionByName(this, FName("Player.Ability.Dash"));
}

void AMGCharacter::StartFireProjectile()
{
	ActionComp->StartActionByName(this, FName("Player.Ability.FireProjectile"));
}

void AMGCharacter::StartSprint()
{
	ActionComp->StartActionByName(this, FName("Player.Ability.Sprint"));
}

void AMGCharacter::StopSprint()
{
	ActionComp->StopActionByName(this, FName("Player.Ability.Sprint"));
}

void AMGCharacter::Interact()
{
	InteractionComp->OnInteract();
}

UMGAttributeComponent* AMGCharacter::GetAttributeComponent() const
{
	return AttributeComp;
}
