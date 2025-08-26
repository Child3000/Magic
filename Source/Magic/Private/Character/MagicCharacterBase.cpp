// Copyright Bear Child


#include "Character/MagicCharacterBase.h"

AMagicCharacterBase::AMagicCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
}

void AMagicCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
