// Copyright Bear Child


#include "Character/MGCharacterBase.h"

const FName AMGCharacterBase::WeaponHandSocketName = "WeaponHandSocket";

AMGCharacterBase::AMGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), WeaponHandSocketName);
}

void AMGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
