// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MagicInteractGuide.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMagicInteractGuide : public UInterface
{
	GENERATED_BODY()
};

/**
 * Inherited by interactable objects or characters that wish to customize its guide behaviour.
 */
class MAGIC_API IMagicInteractGuide
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// called when user is pointing its cursor on the object.
	virtual void OnShowInteractGuide() = 0;
	
	// called when user move its cursor from the object.
	virtual void OnHideInteractGuide() = 0;
};
