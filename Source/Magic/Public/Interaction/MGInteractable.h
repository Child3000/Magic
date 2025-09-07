// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MGInteractorInfo.h"
#include "MGInteractable.generated.h"


// This class does not need to be modified.
UINTERFACE()
class MAGIC_API UMGInteractable : public UInterface
{
	GENERATED_BODY()
};


class MAGIC_API IMGInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:
	/* Returns true if the actor is interactable at the moment; otherwise, false. */
	virtual bool IsInteractableNow();
	
	virtual void Interact(const FMGInteractorInfo& Info);

	virtual void OnShowInteractGuide();
	
	virtual void OnHideInteractGuide();
};
