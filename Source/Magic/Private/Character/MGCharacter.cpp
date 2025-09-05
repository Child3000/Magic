// Copyright Bear Child


#include "Character/MGCharacter.h"

#include "Action/MGActionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Projectile/MGProjectileBase.h"

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
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	ActionComp = CreateDefaultSubobject<UMGActionComponent>("ActionComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->GravityScale = 1.2;
	GetCharacterMovement()->JumpZVelocity = 500;
	GetCharacterMovement()->AirControl = 1.0;
}

void AMGCharacter::StartJump()
{
	ActionComp->StartActionByName(this, FName("Player.Ability.Jump"));
}

void AMGCharacter::StopJump()
{
	ActionComp->StopActionByName(this, FName("Player.Ability.Jump"));
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
