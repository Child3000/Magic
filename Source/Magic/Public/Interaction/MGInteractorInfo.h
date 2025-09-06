#pragma once

#include "CoreMinimal.h"

/*
 * The info provided to objects when interaction occurred.
 */
struct FMGInteractorInfo
{
	// default constructor.
	FMGInteractorInfo()
	{
		FMGInteractorInfo(nullptr);
	}

	// constructor.
	FMGInteractorInfo(AActor* Instigator)
	{
		this->Instigator = Instigator;
	}

	// the source whom cause the interaction to occur.
	TWeakObjectPtr<AActor> Instigator;
};
