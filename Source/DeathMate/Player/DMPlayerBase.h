// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DMPlayerBase.generated.h"

class UInputMappingContext;
class UInputComponent;
class UEnhancedInputComponent;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class DEATHMATE_API ADMPlayerBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ADMPlayerBase();

private:
	UInputMappingContext* IMC_PlayerInput;

protected:
	UCharacterMovementComponent* MoveComp;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
};
