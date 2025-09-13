// Copyright Bear Child


#include "Tag/MGObjectTagComponent.h"

#include "Tag/MGObjectTagAsset.h"


UMGObjectTagComponent::UMGObjectTagComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMGObjectTagComponent::BeginPlay()
{
	Super::BeginPlay();
	AddTags(InitialTagContainerInline);
	if (InitialTagContainer)
	{
		AddTags(*InitialTagContainer);
	}
}

const FGameplayTagContainer& UMGObjectTagComponent::GetTagContainer() const
{
	return TagContainer;
}

void UMGObjectTagComponent::AddTags(const FGameplayTagContainer& Tags)
{
	TagContainer.AppendTags(Tags);
}

void UMGObjectTagComponent::AddTags(const UMGObjectTagAsset& Tags)
{
	AddTags(Tags.TagContainer);
}

void UMGObjectTagComponent::RemoveTags(const FGameplayTagContainer& Tags)
{
	TagContainer.RemoveTags(Tags);
}

bool UMGObjectTagComponent::HasAnyTags(const FGameplayTagContainer& Tags) const
{
	return TagContainer.HasAny(Tags);
}

bool UMGObjectTagComponent::HasAnyTags(const UMGObjectTagAsset& Tags) const
{
	return HasAnyTags(Tags.TagContainer);
}

