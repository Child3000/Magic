// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/MGInteractable.h"
#include "MGDoor.generated.h"

UENUM()
enum class EDoorState
{
	// open forward state.
	OpenForward UMETA(DisplayName = "OpenForward"), 

	// open backward state.
	OpenBackward UMETA(DisplayName = "OpenBackward"),
	
	// close state.
	Close UMETA(DisplayName = "Close"),
};

UCLASS()
class MAGIC_API AMGDoor : public AActor, public IMGInteractable
{
	GENERATED_BODY()

	//~Begin Constructor
public:
	AMGDoor();
	
	//~End Constructor

	
	//~Begin Overrides
protected:
	virtual void BeginPlay() override;
	
	//~End Overrides

	
	//~Begin Component Declaration
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> MeshRotator;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	//~End Component Declaration


	//~Begin Variable Declaration
private:
	/* The target absolute yaw value. The value is always >= 0. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float TargetYaw;

	/* The initial state of door. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	EDoorState InitialState;
	
	//~End Variable Declaration

	
	//~ Begin IMGInteractable Interface
public:
	virtual void Interact(const FMGInteractorInfo& Info) override;
	
	//~ End IMGInteractable Interface

	//~Begin DOOR
private:
	EDoorState CurrentState;
	
	void SetDoorState(EDoorState NewState);
	
	bool IsOpened(EDoorState State);

	FString GetStateDisplayName(EDoorState State);
	
	//~End DOOR
};
