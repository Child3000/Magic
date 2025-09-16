// Copyright Bear Child


#include "Attributes/MGAttributeComponent.h"


UMGAttributeComponent::UMGAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MinHealth = 0;
	MaxHealth = 100;
	Health = 100;
}

void UMGAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Attributes Begin

void UMGAttributeComponent::SetHealth(float NewHealth)
{
	const float OldHealth = Health;
	
	Health = FMath::Clamp(NewHealth, MinHealth, MaxHealth);

	if (Health != OldHealth)
	{
		OnHealthChanged.Broadcast(MakeHealthChangedInfo());
	}
	UE_LOG(LogTemp, Log, TEXT("Current Health is %f"), Health);
}

void UMGAttributeComponent::AddHealth(float HealthDelta)
{
	SetHealth(Health + HealthDelta);
}

void UMGAttributeComponent::RegisterCall_OnHealthChanged(FOnHealthChangedSignature::FDelegate&& Delegate)
{
	Delegate.ExecuteIfBound(MakeHealthChangedInfo());
	OnHealthChanged.Add(MoveTemp(Delegate));
}

FHealthChangedInfo UMGAttributeComponent::MakeHealthChangedInfo() const
{
	FHealthChangedInfo Info;
	Info.Set(Health, MaxHealth, MinHealth);
	return Info;
}

// Attributes End
