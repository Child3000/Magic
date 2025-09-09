// Copyright Bear Child


#include "InteractableObjects/MGExplosiveBarrel.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "PhysicsEngine/RadialForceComponent.h"


AMGExplosiveBarrel::AMGExplosiveBarrel()
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

void AMGExplosiveBarrel::Interact(const FMGInteractorInfo& Info)
{
	IMGInteractable::Interact(Info);

	RadialForceComponent->FireImpulse();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplodeEffect, GetActorLocation());
}

