// Copyright Bear Child


#include "Character/MagicMonster.h"


// Sets default values
AMagicMonster::AMagicMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMagicMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMagicMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

