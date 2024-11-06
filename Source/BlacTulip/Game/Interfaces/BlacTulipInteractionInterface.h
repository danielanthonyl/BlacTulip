// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BlacTulipInteractionInterface.generated.h"

class ABlacTulipCharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBlacTulipInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLACTULIP_API IBlacTulipInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual ABlacTulipCharacter* GetOverlappingCharacter() = 0;
	virtual void Interact(class ABlacTulipCharacter& Character) = 0;
	virtual void EndInteraction() = 0;
};
