// Copyright Bear Child


#include "Character/MGCharacterBase.h"

AMGCharacterBase::AMGCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponHandSocketName = "Socket_Hand_Weapon";
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), WeaponHandSocketName);
}

USkeletalMeshComponent* AMGCharacterBase::GetWeaponMesh() const
{
	return Weapon;
}

void AMGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
