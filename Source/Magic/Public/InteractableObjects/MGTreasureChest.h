// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/MGInteractable.h"
#include "MGTreasureChest.generated.h"

struct FMGInteractorInfo;

UCLASS()
class MAGIC_API AMGTreasureChest : public AActor, public IMGInteractable
{
	GENERATED_BODY()

public:
	AMGTreasureChest();

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	virtual void Interact(const FMGInteractorInfo& Info) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TreasureChest", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TreasureChest", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> LidMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TreasureChest", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> LidMeshRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TreasureChest", meta = (AllowPrivateAccess = "true"))
	bool bInitialOpened;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TreasureChest", meta = (AllowPrivateAccess = "true"))
	float LidOpenedRoll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TreasureChest", meta = (AllowPrivateAccess = "true"))
	float LidClosedRoll;
	
protected:
	uint32 _bChestOpened:1;
	
	void ActivateChest(bool bActivate);
	
	bool IsChestOpened() const;
};
