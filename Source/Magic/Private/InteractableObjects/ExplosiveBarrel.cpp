// Copyright Bear Child


#include "InteractableObjects/ExplosiveBarrel.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "PhysicsEngine/RadialForceComponent.h"


AExplosiveBarrel::AExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetCollisionProfileName(FName("PhysicsActor"));
	MeshComponent->BodyInstance.bLockXTranslation = true;
	MeshComponent->BodyInstance.bLockYTranslation = true;
	MeshComponent->BodyInstance.bLockZTranslation = false;
	MeshComponent->BodyInstance.bLockXRotation = true;
	MeshComponent->BodyInstance.bLockYRotation = true;
	MeshComponent->BodyInstance.bLockZRotation = true;
	
	SetRootComponent(MeshComponent);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComponent->Radius = 500;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->SetupAttachment(MeshComponent);
}

void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnComponentHit);
}

void AExplosiveBarrel::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplodeEffect, GetActorLocation());
}

