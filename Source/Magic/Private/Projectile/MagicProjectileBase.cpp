// Copyright Bear Child


#include "Projectile/MagicProjectileBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AMagicProjectileBase::AMagicProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileComp->InitialSpeed = 1500;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->ProjectileGravityScale = 0.7f;
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>("Niagara");
	NiagaraComp->SetupAttachment(RootComponent);
	NiagaraComp->bAutoActivate = true;
}

void AMagicProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &AMagicProjectileBase::ProjectileHit);
}

void AMagicProjectileBase::Destroyed()
{
	Super::Destroyed();
	if (ExplodedEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplodedEffect, GetActorLocation(), GetActorRotation());
	}
}

void AMagicProjectileBase::ProjectileHit(UPrimitiveComponent* HitComp,
                                         AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp,
                                         FVector NormalImpulse,
                                         const FHitResult& Hit)
{
	if (IsValid(this))
	{
		Destroy();
	}
}

