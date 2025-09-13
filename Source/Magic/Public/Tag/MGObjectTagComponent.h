// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "MGObjectTagComponent.generated.h"


class UMGObjectTagAsset;
/*
 * The tag container for object.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGIC_API UMGObjectTagComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMGObjectTagComponent();

protected:
	virtual void BeginPlay() override;

public:
	const FGameplayTagContainer& GetTagContainer() const;

	void AddTags(const FGameplayTagContainer& Tags);
	
	void AddTags(const UMGObjectTagAsset& Tags);

	void RemoveTags(const FGameplayTagContainer& Tags);

	bool HasAnyTags(const FGameplayTagContainer& Tags) const;

	bool HasAnyTags(const UMGObjectTagAsset& Tags) const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer InitialTagContainerInline;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tags")
	TObjectPtr<UMGObjectTagAsset> InitialTagContainer;
	
	FGameplayTagContainer TagContainer;
};
