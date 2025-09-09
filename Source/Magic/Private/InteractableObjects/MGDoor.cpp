// Copyright Bear Child


#include "InteractableObjects/MGDoor.h"


// CONSTRUCTOR
// ----------------------------------------------------------------------
AMGDoor::AMGDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	
	MeshRotator = CreateDefaultSubobject<USceneComponent>("MeshRotator");
	MeshRotator->SetupAttachment(Root);
	MeshRotator->SetRelativeLocation(FVector(0, 100, 0));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(MeshRotator);
	Mesh->SetRelativeLocation(FVector(0, -100, 0));
	Mesh->SetRelativeRotation(FRotator(0, -90, 0));

	TargetYaw = 90.0f;
	InitialState = EDoorState::Close;
}


// OVERRIDES
// ----------------------------------------------------------------------
void AMGDoor::BeginPlay()
{
	Super::BeginPlay();

	SetDoorState(InitialState);
}


// IMGInteractable Interface
// ----------------------------------------------------------------------
void AMGDoor::Interact(const FMGInteractorInfo& Info)
{
	IMGInteractable::Interact(Info);

	if (!Info.Instigator.Get())
	{
		return;
	}

	if (IsOpened(CurrentState))
	{
		SetDoorState(EDoorState::Close);
	}
	else
	{
		const FVector DoorLocation = GetActorLocation();
		const FVector InteractorLocation = Info.Instigator->GetActorLocation();
		const FVector DoorFaceDir = GetActorForwardVector();
		const FVector InteractorToDoorDir = (DoorLocation - InteractorLocation).GetSafeNormal();
		const float DotProduct = FVector::DotProduct(DoorFaceDir, InteractorToDoorDir);
	
		const bool bLocatedFrontDoor = DotProduct < 0;
		SetDoorState(bLocatedFrontDoor ? EDoorState::OpenBackward : EDoorState::OpenForward);
	}
}


// Door
// ----------------------------------------------------------------------
void AMGDoor::SetDoorState(EDoorState NewState)
{
	CurrentState = NewState;
	
	switch (NewState)
	{
	case EDoorState::Close:
		MeshRotator->SetRelativeRotation(FRotator(0, 0, 0));
		break;

	case EDoorState::OpenForward:
		MeshRotator->SetRelativeRotation(FRotator(0, FMath::Abs(TargetYaw), 0));
		break;

	case EDoorState::OpenBackward:
		MeshRotator->SetRelativeRotation(FRotator(0, -FMath::Abs(TargetYaw), 0));
		break;
	}
}

bool AMGDoor::IsOpened(EDoorState State)
{
	const FString DisplayName = GetStateDisplayName(State);
	return DisplayName.Contains("Open");
}

FString AMGDoor::GetStateDisplayName(EDoorState State)
{
	const UEnum* EnumPtr = StaticEnum<EDoorState>();
	if (!EnumPtr) return FString("");

	return EnumPtr->GetDisplayNameTextByValue((int64)State).ToString();
}