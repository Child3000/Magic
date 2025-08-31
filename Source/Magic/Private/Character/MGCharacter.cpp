// Copyright Bear Child


#include "Character/MGCharacter.h"

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

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	WeaponProjectileSpawnSocketName = FName("Socket_ProjectileSpawn");
}

void AMGCharacter::FireProjectile()
{
	FVector SpawnLocation = Weapon->GetSocketLocation(WeaponProjectileSpawnSocketName);
	FRotator SpawnRotation = GetActorRotation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation, SpawnParams);
}
