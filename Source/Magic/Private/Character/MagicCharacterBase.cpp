// Copyright Bear Child


#include "Character/MagicCharacterBase.h"

const FName AMagicCharacterBase::WeaponHandSocketName = "WeaponHandSocket";

AMagicCharacterBase::AMagicCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), WeaponHandSocketName);
}

void AMagicCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
