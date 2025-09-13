// Copyright Bear Child


#include "Projectile/MGProjectileBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Tag/MGObjectTagComponent.h"


AMGProjectileBase::AMGProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	TagComp = CreateDefaultSubobject<UMGObjectTagComponent>("ObjectTag");
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;
	
	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileComp->InitialSpeed = 1500;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->ProjectileGravityScale = 0;
	
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>("Niagara");
	NiagaraComp->SetupAttachment(RootComponent);
	NiagaraComp->bAutoActivate = true;
}

void AMGProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this, &AMGProjectileBase::ProjectileHit);

	// ignore collision with the projectile's owner.
	SphereComp->IgnoreActorWhenMoving(GetOwner(), true);
}

void AMGProjectileBase::Destroyed()
{
	Super::Destroyed();
	if (ExplodedEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplodedEffect, GetActorLocation(), GetActorRotation());
	}
}

void AMGProjectileBase::ProjectileHit(UPrimitiveComponent* HitComp,
                                         AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp,
                                         FVector NormalImpulse,
                                         const FHitResult& Hit)
{
	Destroy();
}

