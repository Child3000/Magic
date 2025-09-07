// Copyright Bear Child


#include "InteractableObjects/MGTreasureChest.h"

#include "Interaction/MGInteractorInfo.h"


AMGTreasureChest::AMGTreasureChest()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMesh);

	LidMeshRotator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidRotator"));
	LidMeshRotator->SetupAttachment(BaseMesh);
	
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(LidMeshRotator);

	bInitialOpened = false;
	LidOpenedRoll = -120;
	LidClosedRoll = 0;
	_bChestOpened = false;
}


void AMGTreasureChest::BeginPlay()
{
	Super::BeginPlay();

	// Set up initial state of treasure chest.
	ActivateChest(bInitialOpened);
}


#if WITH_EDITOR
void AMGTreasureChest::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = PropertyChangedEvent.GetPropertyName();
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AMGTreasureChest, bInitialOpened))
	{
		ActivateChest(bInitialOpened);
	}
}
#endif


void AMGTreasureChest::Interact(const FMGInteractorInfo& Info)
{
	IMGInteractable::Interact(Info);

	if (!Info.Instigator.Get())
	{
		return;
	}

	// Open the chest.
	ActivateChest(!IsChestOpened());
}


void AMGTreasureChest::ActivateChest(bool bActivate)
{
	// Mark chest opened.
	_bChestOpened = bActivate;
	
	FRotator NewRotator = bActivate ? FRotator(0, 0, LidOpenedRoll) : FRotator(0, 0, LidClosedRoll);
	LidMeshRotator->SetRelativeRotation(NewRotator);
}


bool AMGTreasureChest::IsChestOpened() const
{
	return _bChestOpened;
}

